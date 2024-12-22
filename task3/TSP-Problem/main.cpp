#include "userParse.hpp"
#include "geneticAlg.hpp"

#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>
#include <chrono>

#include "benchmark/benchmark.h" // install google-benchmark to test

// #define TEST // it's activated through the makefile

#ifdef TEST

void fill_data(geneticAlg & genetic_obj, userParse & parse_obj, int city, int gen, int tour, int percent) {

    std::cout << city << " " << gen << " " << tour << " " << percent << std::endl;

    assert(city > 0);
    parse_obj.setCities(city);

    // load data from file
    parse_obj.loadArray();
    parse_obj.fillStartArray();

    assert(gen > 0);
    genetic_obj.setGeneration(gen);

    assert(tour > 1); // to provide the correctness of number tours for GA algorithm
    genetic_obj.setTours(tour);

    assert(percent >= 0);
    genetic_obj.setPercentage(percent);
   
}

double genetic_algo(geneticAlg & genetic_obj, userParse & parse_obj) {
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

    return finalLowest;
}

double brute_force_algo(userParse & parse_obj) {
    // brute force algorithm to find the optimal tour distance
    std::vector<std::string> bruteVec = parse_obj.permute(parse_obj.findFactorial(parse_obj.getCities()));
    double cost = 10000;
    double lowest = 10000;
    for (int i = 0; i < bruteVec.size(); ++i) {
        std::string temp1 = bruteVec.at(i);
        cost = parse_obj.findCost(temp1);
        if(cost < lowest) {
            lowest = cost;
        }
    }

    return lowest;
}


void make_args(benchmark::internal::Benchmark * benchmark) 
{
    for (auto city = 9; city < 10; ++city){
        if (city % 4 == 0) continue;
        for (auto gen = 1; gen < 100; gen += 10) {
            for (auto tour = 2; tour < 7; tour += 2) {
                for (auto percent = 0; percent < 100; percent += 50) {
                    benchmark->Args({ city, gen, tour, percent });
                }
            }
        }    
    } 
}

void test_genetic(benchmark::State & state) {

    for (auto value : state) {

        geneticAlg genetic_obj;
        userParse parse_obj;

        fill_data(genetic_obj, parse_obj, state.range(0), state.range(1), state.range(2), state.range(3));
        
        // std::cout << "-------------------------------------------" << std::endl;
        // std::cout << "Number of cities run: " << parse_obj.getCities() << std::endl;

        auto start = std::chrono::high_resolution_clock::now();
        double final_lowest = genetic_algo(genetic_obj, parse_obj);
        auto end = std::chrono::high_resolution_clock::now();
        
        std::cout << "-------------------------------------------" << std::endl;
        std::cout << "Genetic algorithm cost: " << final_lowest << std::endl;

        auto elapsed_time = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
        // auto elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        state.SetIterationTime(elapsed_time.count());
        // std::cout << "GA algorithm: " << elapsed_time << std::endl;

        // int totalPer = (final_lowest/lowest) * 100;
        // std::cout << "The GA produced a solution that is " << totalPer << "% of the optimal solution." << std::endl;
        
        // benchmark::DoNotOptimize(&func);
    }

    state.SetComplexityN(state.range(0));

}


void test_brute_force(benchmark::State & state) {

    for (auto value : state) {

        geneticAlg genetic_obj;
        userParse parse_obj;

        fill_data(genetic_obj, parse_obj, state.range(0), state.range(1), state.range(2), state.range(3));
        
        auto start = std::chrono::high_resolution_clock::now();
        double lowest = brute_force_algo(parse_obj);
        auto end = std::chrono::high_resolution_clock::now();

        std::cout << "-------------------------------------------" << std::endl;
        std::cout << "Optimal Brute force cost: " << lowest << std::endl;

        auto elapsed_time = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
        // elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        state.SetIterationTime(elapsed_time.count());
        // std::cout << "Brute force algorithm: " << elapsed_time << std::endl;

        // int totalPer = (final_lowest/lowest) * 100;
        // std::cout << "The GA produced a solution that is " << totalPer << "% of the optimal solution." << std::endl;
        

        // benchmark::DoNotOptimize(&func);
    }
    state.SetComplexityN(state.range(0));

}
// kMicrosecond
BENCHMARK(test_genetic)->Apply(make_args)->Iterations(1)->UseManualTime()->Unit(benchmark::kMillisecond); //->Complexity();
BENCHMARK(test_brute_force)->Apply(make_args)->Iterations(1)->UseManualTime()->Unit(benchmark::kMillisecond); //->Complexity();


BENCHMARK_MAIN();


#else 

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
    auto start = std::chrono::high_resolution_clock::now();

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

    auto stop = std::chrono::high_resolution_clock::now();
    auto elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << "-------------------------------------------" << std::endl;
    std::cout << "GA algorithm: " << elapsed_time << std::endl;
    std::cout << "Genetic algorithm cost: "<< finalLowest << std::endl;


    start = std::chrono::high_resolution_clock::now();
    
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

    stop = std::chrono::high_resolution_clock::now();
    elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    // brute force algorithm output
    std::cout << "Brute force algorithm: " << elapsed_time << std::endl;
    std::cout<<"Optimal Brute force cost: " << lowest << std::endl;

    int totalPer = (finalLowest/lowest) * 100;
    std::cout<<"The GA produced a solution that is " << totalPer << "% of the optimal solution." <<std::endl;

    return 0;
}

#endif // TEST

