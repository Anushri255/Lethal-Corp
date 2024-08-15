#include "CorporationMoon.h"
#include <iostream>
#include "Game.h"



CorporationMoon::CorporationMoon(const std::string& name) : AbstractMoon(name) {
}

void CorporationMoon::sendEmployee(const int& employeeCount, Game& g) {
    std::cout << "\nThis command is not available on this moon" << std::endl;
}

void CorporationMoon::sellCargo(const int& value, Game& g) {

    if (value > g.getCargoValue()) {
        std::cout << "\nOnly $" << g.getCargoValue() << " available in cargo." << std::endl;
    
    } else if (value == 0) {
        std::cout << "\nNothing to sell." << std::endl;
    
    } else {
        g.setBalance(value + g.getBalance());
        g.setCargoValue(g.getCargoValue() - value);
        std::cout << "\nYour service is invaluable to the corporation." << std::endl;
        std::cout << "New balance : $" << g.getBalance() << "(quota is $" << g.getQuota() << ")" << std::endl;
        std::cout << "New cargo value: $" << g.getCargoValue() << std::endl;
    }

};