#include "userParse.hpp"
#include "geneticAlg.hpp"

#include <iostream>
#include <vector>
#include <sys/time.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cassert>

int main() {

    geneticAlg genetic_obj;
    userParse parse_obj;

    std::cout << "Enter the number of cities: " << std::endl;
    int cityTemp;
    std::cin >> cityTemp;
    assert(cityTemp > 0);
    parse_obj.setCities(cityTemp);

    // load data from file
    parse_obj.loadArray();
    parse_obj.fillStartArray();

    std::cout << "Enter the number of generations: " << std::endl;
    int genTemp;
    std::cin >> genTemp;
    assert(genTemp > 0);
    genetic_obj.setGeneration(genTemp);

    std::cout << "Enter the number of tours: " << std::endl;
    int toursTemp;
    std::cin >> toursTemp;
    assert(toursTemp > 1); // to provide the correctness of number tours for GA algorithm
    genetic_obj.setTours(toursTemp);

    std::cout << "Enter the percentage of mutations: " << std::endl;
    int perTemp;
    std::cin >> perTemp;
    assert(perTemp >= 0);
    genetic_obj.setPercentage(perTemp);
    
    std::cout << "-------------------------------------------" << std::endl;
    std::cout << "Number of cities run: " << parse_obj.getCities() << std::endl;

    // measure the time 
    struct timeval * t;
    t = (struct timeval *)malloc(sizeof(struct timeval));
    gettimeofday(t,NULL);
    time_t startSec = t->tv_sec;

    // compute the number of mutated tours needed
    int numMut = genetic_obj.getTours() * genetic_obj.getPercentage() / 100;
    double finalCost = 100000;
    double finalLowest = 10000;

    for (int k = 0; k < genetic_obj.getGeneration(); ++k) {

        std::vector<std::string> temp1 = parse_obj.permute(genetic_obj.getTours());
        std::vector<std::string> elites;
        std::vector<std::string> total;
        std::string elite;

        //select two elites from each generation
        for (int j = 0; j < 2; ++j) {
            double lowest1 = 100000;
            double cost1 = 100000;
            int index;

            for (int i = 0; i < temp1.size(); ++i) {
                std::string tempS = temp1.at(i);
                cost1 = parse_obj.findCost(tempS);
                if(cost1 < lowest1) {
                    lowest1 = cost1;
                    elite = temp1.at(i);
                    elites.push_back(elite);
                    index = i;
                }
            }
            elites.at(j) = temp1.at(index);
            temp1.erase(temp1.begin() + index);
        }

        //create mutations by switching out 3 cities
        for (int l = 0; l < numMut; ++l) {
            char tempC, tempC2, tempC3;
            std::string tempString;
            if(l % 2 == 0) { 
                tempString = elites.at(1);
                tempC = tempString[1];
                tempC2 = tempString[2];
                tempC3 = tempString[3];
                tempString[1] = tempC2;
                tempString[2] = tempC3;
                tempString[3] = tempC;
                total.push_back(tempString);
            } else {
                tempString = elites.at(0);
                tempC = tempString[1];
                tempC2 = tempString[2];
                tempC3 = tempString[3];
                tempString[1] = tempC3;
                tempString[2] = tempC;
                tempString[3] = tempC2;
                total.push_back(tempString);
            }
        }

        // fill the rest of the tour up with fresh permutations
        std::vector<std::string> perms = parse_obj.permute(genetic_obj.getTours() - total.size());
        for (int n = 0; n < perms.size(); ++n) {
            total.push_back(perms.at(n));
        }

        // compute the lowest cost tour
        for (int i = 0; i < genetic_obj.getTours(); ++i) {
            std::string stringTemp = total.at(i);
            finalCost = parse_obj.findCost(stringTemp);
            if(finalCost < finalLowest) {
                finalLowest = finalCost;
            }
        }
    }

    std::cout << "-------------------------------------------" << std::endl;
    gettimeofday(t, NULL);
    std::cout << "GA algorithm: " << t->tv_sec - startSec << " s, " << t->tv_usec <<" us" << std::endl;
    std::cout << "Genetic algorithm cost: "<< finalLowest << std::endl;


    // brute force algorithm to find the optimal tour distance
    std::vector<std::string> bruteVec = parse_obj.permute(parse_obj.findFactorial(parse_obj.getCities()));
    double cost = 10000;
    double lowest = 10000;
    for (int i = 0; i < bruteVec.size(); ++i) {
        std::string temp1 = bruteVec.at(i);
        cost = parse_obj.findCost(temp1);
        if(cost < lowest){
            lowest = cost;
        }
    }

    // brute force algorithm output
    gettimeofday(t,NULL);

    std::cout << "Brute force algorithm: " << t->tv_sec - startSec << " s, " << t->tv_usec <<" us" << std::endl;
    std::cout<<"Optimal Brute force cost: " << lowest << std::endl;

    int totalPer;
    totalPer = (finalLowest/lowest) * 100;
    std::cout<<"The GA produced a solution that is " << totalPer << "% of the optimal solution." <<std::endl;

    return 0;
}
