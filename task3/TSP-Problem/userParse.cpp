#include "userParse.hpp"
#include <iostream>
#include <fstream>
#include <vector>

int userParse::getCities() {
    return city;
}

void userParse::setCities(int city) {
    this->city = city;
}

void userParse::fillStartArray() {
    for (int i = 1; i < city; ++i) {
        s[i] = i;
    }
}

// load a 2d matrix with the distance.txt information
void userParse::loadArray() {
    std::ifstream inFile{"distances.txt"};
    if (!inFile) {
        std::cout<<"Cannot open file."<<std::endl;
    }

    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 20; ++j) {
            if(i == j) {
                this->adArray[i][j] = 0;
            } else {
                inFile >> this->adArray[i][j];
            }
        }
    }
}

// return a formatted string of tour destinations
std::string userParse::printS() {
    std::string tempString;
    s[0] = 0;
    s[city+1] = 0;

    for (int i = 0; i < city+1; ++i) {
        tempString.push_back(s[i] + '0');
    }
    return tempString;
}

// return a vector of n permuted tour strings
std::vector<std::string> userParse::permute(int permsThisCall) {
    std::vector<std::string> storage;

    int m, k, p, q, i;
    int NUMELEMENTS = city;

    std::string temp = printS();
    storage.push_back(temp);
    for(i = 1; i < permsThisCall; i++)
    {
        m = NUMELEMENTS-2;
        while(s[m]>s[m+1])
        {
            m = m - 1;
        }
        k = NUMELEMENTS-1;
        while(s[m] > s[k])
        {
            k = k - 1;
        }
        std::swap(s[m],s[k]);
        p = m + 1;
        q = NUMELEMENTS-1;
        while( p < q)
        {
            std::swap(s[p],s[q]);
            p++;
            q--;
        }
        std::string temp = printS();
        storage.push_back(temp);
    }
    
    return storage;
}

// find the factorial of a given n number
int userParse::findFactorial(int num) {
    if(num > 1) {
        return num * findFactorial(num - 1);
    } else {
        return 1;
    }
}

// find the cost associated with a given tour
double userParse::findCost(std::string temp) {
    int tempArr[city];
    double cost;

    for (int j = 0; j < temp.length(); ++j) {
        tempArr[j] = temp[j] - '0';
    }

    for (int i = 0; i < city; ++i) {
        cost = adArray[tempArr[i]][tempArr[i+1]] + cost;
    }
    return cost;
}

// auxilary function used for testing individual destination costs
double userParse::findCostTemp(int x, int y) {
    double temp;
    temp = adArray[x][y];
    return temp;
}