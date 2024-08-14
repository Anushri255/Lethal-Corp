#ifndef REGULARMOON
#define REGULARMOON


#include "AbstractMoon.h"


class RegularMoons : public AbstractMoon {

private:
    int _minScrapValue;
    int _maxScrapValue;
    double _baseSurvivalChance;
    double _travelFee;

public:
    RegularMoons(const std::string& name, const int& minScrapValue, const int& maxScrapValue,const double& baseSurvivalChance, const double& travelFee = 0);

    virtual void sendEmployee(const int& employeeCount, Game& g) override;

    virtual void sellCargo(const int& value, Game& g) override;

    const double& getTravelFee() const;

};



#endif // REGULARMOON