#include "geneticAlg.hpp"

int geneticAlg::getGeneration() {
    return gen;
}

void geneticAlg::setGeneration(int gen) {
    this->gen = gen;
}

void geneticAlg::setTours(int tours) {
    this->tours = tours;
}

int geneticAlg::getTours() {
    return tours;
}

void geneticAlg::setPercentage(int percentage) {
    this->percentage = percentage;
}

int geneticAlg::getPercentage() {
    return percentage;
}
