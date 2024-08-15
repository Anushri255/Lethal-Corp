#include "RandomGenerator.h"
#include <iostream>

RandomGenerator::RandomGenerator() : _randomGenerator(std::random_device{}()) {}

const double RandomGenerator::generateUniformDistribution(const double& min, const double& max) {
    std::uniform_int_distribution<int> intDistribution(min, max);
    auto randomNumber = intDistribution(_randomGenerator);
    return randomNumber;
}

const float RandomGenerator::generateFloatDistribution(const double& min, const double& max) {
    std::uniform_real_distribution<double> floatDistribution(min, max);
    auto randomFloat = floatDistribution(_randomGenerator);
    return randomFloat;
}