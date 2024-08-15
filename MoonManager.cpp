#include "MoonManager.h"
#include <iostream>
#include "Game.h"
#include "AbstractMoon.h"
#include "util.h"
#include <vector>
#include "RegularMoons.h"


MoonManager:: MoonManager() {}

const std::vector<AbstractMoon*>& MoonManager::getMoonsList() const {
    return _moonsList;

}

void MoonManager::registerMoon(AbstractMoon* moon) {
    _moonsList.push_back(moon);
}


void MoonManager::showMoons(const Game& g) const {
    std::cout << "\nWelcome to the exomoons catalogue." << std::endl;
    std::cout << "To route the autopilot to a moon, use the word ROUTE." << std::endl;
    std::cout << "---------------------------------------" << std::endl;
    
    for (const auto& moonPtr : _moonsList) {

        // Display the weather of the moon
        if (moonPtr->getWeather() != "Clear") {
            std::cout << "\n* " << moonPtr->name() << " (" << moonPtr->getWeather() << ")";

        } else {
            std::cout << "\n* " << moonPtr->name();
        }

        // Display travel fee of the moon
        if (auto* regularMoon = dynamic_cast<RegularMoons*>(moonPtr)) {

            if (regularMoon->getTravelFee() > 0) {
                std::cout << ": $" << regularMoon->getTravelFee();
            }

        }


    }
    std::cout << "\n\nBalance: $" << g.getBalance() << std::endl;
    
}

void MoonManager::routeMoon(Game& g, const std::string& _moonName) {

    for (auto& moonPtr : _moonsList) {

        std::string currentMoonName = moonPtr->name();
        util::lower(currentMoonName);

        if (currentMoonName == _moonName) { 

            if (auto* regularMoon = dynamic_cast<RegularMoons*>(moonPtr)) {

                if (regularMoon->getTravelFee() > 0) {

                    // Not enough balance to travel to moon
                    if (regularMoon->getTravelFee() > g.getBalance()) {
                        std::cout << "You don't have enough balance to travel to " << moonPtr->name() << std::endl;
                        std::cout << "Trip cancelled.\nStill orbiting " << g.getCurrentMoon().name() << "." << std::endl;
                        return;

                    } else {

                        auto validInput = false;

                        while (validInput == false) {

                            std::cout << "\nThe cost of going to " << moonPtr->name() << " is $" << regularMoon->getTravelFee() << std::endl;
                            std::cout << "You have $" << g.getBalance() << ". Confirm destination? [Yes/No]" << std::endl;

                            std::string userChoice;
                            std::getline(std::cin, userChoice);
                            util::lower(userChoice);

                            if (userChoice == "yes") {
                                // Deduct travel fees from balance
                                g.setBalance(g.getBalance() - regularMoon->getTravelFee());
                                g.setCurrentMoon(moonPtr);

                                std::cout << "New balance $" << g.getBalance() << std::endl;
                                std::cout << "Now orbiting " << g.getCurrentMoon().name() << ". Use the LAND command to land." << std::endl;
                                validInput = true;
                                std::cin.clear();
                                return;

                            // User doesn't want to travel to the moon
                            } else if (userChoice == "no") {
                                std::cout << "Trip cancelled.\nStill orbiting " << g.getCurrentMoon().name() << "." << std::endl;
                                validInput = true;
                                std::cin.clear();
                                return;

                            } else {
                                std::cout << "Invalid input. Choose one of the following options [Yes/No]" << std::endl;
                            }

                        }
                       
                    }       
                }
            }
            g.setCurrentMoon(moonPtr);
            std::cout << "\nNow orbiting " << g.getCurrentMoon().name() << ". Use the LAND command to land." << std::endl;
            return;
        }
    }
    std::cout << "\nUnknown moon '" << _moonName << "'." << std::endl;
}

void MoonManager::setMoonsWeather(Game& g) {

    for (auto& moonPtr : _moonsList) {

        // Randomly set the weather of the moon unless its Corporation
        if(moonPtr->name() != "Corporation") {
            moonPtr->setMoonWeather(static_cast<MoonWeather>(g.getRandomGenerator().generateUniformDistribution(0, 3)));
        } else {
            // Weather for Corporation moon is always clear
            moonPtr->setMoonWeather(static_cast<MoonWeather>(0));
        }
    }


}

MoonManager::~MoonManager() {

    // Deletes the moons in the list
    for (AbstractMoon* moon : _moonsList) {
        delete moon;
    }

    // Delete the moonlist
    _moonsList.clear();
}