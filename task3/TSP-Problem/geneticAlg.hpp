#ifndef GENETICALG_HPP
#define GENETICALG_HPP

#include <string>
#include <iostream>
#include <vector>
#include "userParse.hpp"

class geneticAlg {

public:
    void setGeneration(int gen);
    int getGeneration();

    void setTours(int tours);
    int getTours();

    void setPercentage(int percentage);
    int getPercentage();

private:
    int gen;
    int tours;
    int percentage;
};

#endif //GENETICALG_HPP
