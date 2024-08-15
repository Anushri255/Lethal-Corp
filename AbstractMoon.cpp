#include "AbstractMoon.h"
#include <random>
#include "Game.h"
#include <iostream>


AbstractMoon::AbstractMoon(const std::string& moonName) : _moonName(moonName){}

const std::string& AbstractMoon::name() const {
    return _moonName;
}

void AbstractMoon::onDayBegin(const Game& g) const {
    std::cout << "============= DAY " << g.getDay() << " ============= " << std::endl;
    std::cout << "Current cargo value: $" << g.getCargoValue() << std::endl;
    std::cout << "Current balance: $" << g.getBalance() << std::endl;
    std::cout << "Current quota: $" << g.getQuota() << " (" << g.getRemainingDays() << " days left to meet quota)" << std::endl;
    std::cout << "Currently orbiting: " << g.getCurrentMoon().name() << std::endl;

    std::cout << "\n>MOONS\nTo see the list of moons the autopilot can route to." << std::endl;
    std::cout << "\n>STORE\nTo see the company store's selection of useful items." << std::endl;
    std::cout << "\n>INVENTORY\nTo see the list of items you've already bought." << std::endl;

    if (g.getRemainingDays() == 0) {
        std::cout << "\nNOTE: 0 days left to meet quota. Type 'route corporation' to go to the corp's moon and sell the scrap you collected for cash." << std::endl;
    }
    
}

void AbstractMoon::setMoonWeather(MoonWeather weather)  {
    _moonWeather = weather;
}

const std::string AbstractMoon::getWeather() const {
    switch (_moonWeather) {
    case MoonWeather::Clear:
        return "Clear";
    case MoonWeather::Flooded:
        return "Flooded";
    case MoonWeather::Eclipsed:
        return "Eclipsed";
    case MoonWeather::Stormy:
        return "Stormy";
    default:
        return "";
    }
}