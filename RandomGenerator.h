#ifndef RANDOMGENERATOR_H
#define RANDOMGENERATOR_H

#include <random>

class RandomGenerator {

private:     
    std::mt19937 _randomGenerator;

public:
    RandomGenerator();
    const double generateUniformDistribution(const double& min, const double& max);
    const float generateFloatDistribution(const double& min, const double& max);
    
};


#endif // RANDOMGENERATOR_H



