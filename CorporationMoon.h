#ifndef CORPORATIONMOON
#define CORPORATIONMOON

#include "AbstractMoon.h"


class CorporationMoon : public AbstractMoon {

public:
    CorporationMoon(const std::string& name);

    virtual void sendEmployee(const int& employeeCount, Game& g) override;

    virtual void sellCargo(const int& value, Game& g) override;

};

#endif // CORPORATIONMOON