#include "RegularMoons.h"
#include <iostream>
#include "Game.h"


RegularMoons::RegularMoons(const std::string& name, const int& minScrapValue, const int& maxScrapValue, const double& baseSurvivalChance, const double& travelFee) 
    : AbstractMoon(name), _minScrapValue(minScrapValue), _maxScrapValue(maxScrapValue), _baseSurvivalChance(baseSurvivalChance),_travelFee(travelFee) {
}


void RegularMoons::sendEmployee(const int& numExplorers, Game& g) {
            
            double explorerSurvivalChance = _baseSurvivalChance;
            double operatorSurvivalChance = 1.0;
            double scrapValueMultiplier = 1.0;
            double explorerSaveChance = 0;
            double lootRecoveryMultiplier = 1.0;


            for (const auto& itemPtr : g.getItemManager()->getItemsList()) {

                if (itemPtr->getBought()) {
                    explorerSurvivalChance = explorerSurvivalChance * itemPtr->getExplorerSurvivalChanceMultiplier();
                    operatorSurvivalChance = operatorSurvivalChance * itemPtr->getOperatorSurvivalChanceMultiplier();
                    scrapValueMultiplier = scrapValueMultiplier * itemPtr->getScrapValueMultiplier();
               
                    if (itemPtr->getExplorerSaveChance() != 0) {
                        explorerSaveChance = itemPtr->getExplorerSaveChance();
                    }

                    lootRecoveryMultiplier = lootRecoveryMultiplier * itemPtr->getLootRecoveryMultiplier();
                }
            }


            // Update simulation parameters based on weather conditions
            if (getWeather() == "Flooded") {
                explorerSurvivalChance = explorerSurvivalChance * 0.7;
            
            } else if (getWeather() == "Stormy") {
                scrapValueMultiplier = scrapValueMultiplier * 0.75;
            
            } else if (getWeather() == "Eclipsed") {
                explorerSurvivalChance = explorerSurvivalChance * 0.9;
                operatorSurvivalChance = operatorSurvivalChance * 0.7;
            }

            int deadExplorers = 0;
            int deadOperators = 0;
            int totalRevenue = 0;


            // Simulate explorers
            for (int i = 0; i < numExplorers; ++i) {

                double revenue = g.getRandomGenerator().generateUniformDistribution(_minScrapValue * scrapValueMultiplier, _maxScrapValue * scrapValueMultiplier);


                if (g.getRandomGenerator().generateFloatDistribution(0.0,1.0) < explorerSurvivalChance) {
                    // Explorer survived
                    totalRevenue += revenue;
                
                } else if (g.getRandomGenerator().generateFloatDistribution(0.0, 1.0) >= explorerSaveChance) {
                    // Explorer died and was not saved
                    totalRevenue = totalRevenue + revenue * lootRecoveryMultiplier;
                    deadExplorers++;
                }
 
            }

            // Simulate operators
            for (int i = 0; i < g.getAliveEmployees() - numExplorers; ++i) {
                if (g.getRandomGenerator().generateFloatDistribution(0.0, 1.0) >= operatorSurvivalChance) {
                    // Operator died
                    deadOperators++;
                }
            }
              
            if (deadExplorers + deadOperators >= g.getAliveEmployees()) {
                std::cout << "\nNone of the employees managed to make it back. 0 employees left.\n" << std::endl;
                std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
                std::cout << "All the employees died and the scrap is lost." << std::endl;
                std::cout << "Autopilot will now bring the ship back to orbit." << std::endl;
                std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
                g.setAliveEmployees(g.getAliveEmployees() - (deadExplorers + deadOperators));
                g.setCargoValue(0);
            
            } else {
                g.setAliveEmployees(g.getAliveEmployees() - (deadExplorers + deadOperators));

                if (deadExplorers == numExplorers) {
                    std::cout << "\nNone of the employees managed to make it back. " << g.getAliveEmployees() << " employees left." << std::endl;
                
                } else {
                    std::cout << "\n" <<  (numExplorers - deadExplorers) << " employees made it back to the ship, bringing $"
                        << totalRevenue << " worth of scrap." << deadExplorers << " died." << std::endl;
                    g.setCargoValue(g.getCargoValue() + totalRevenue);

                }

            }

}

void RegularMoons::sellCargo(const int& value, Game& g) {
    std::cout << "\nThis command is not available on this moon" << std::endl;
};


const double& RegularMoons::getTravelFee() const {
    return _travelFee;
}