#include "Game.h"
#include <iostream>
#include "util.h"
#include "RegularMoons.h"
#include "CorporationMoon.h"
#include "Item.h"
#include "RandomGenerator.h"


Game::Game():
    _balance(50),
    _gamePhase("Orbiting"),
    _cargoValue(0),     
    _aliveEmployees(4),
    _itemManager(new ItemManager()),
    _moonManager(new MoonManager()), 
    _randomGenerator(new RandomGenerator()),
    _day(1),
    _quota(150),
    _remainingDays(3)
   {
}

int Game::startGame() {
    setupGame();
    welcomeString();
    _currentMoon->onDayBegin(*this);
    getUserInput();
    std::cout << "Program ended";
    return 0;
}


void Game::exit() {
    std::cout << "\nTill next time..Byee!\n\n" << std::endl;
    delete _moonManager;
    delete _itemManager;
    delete _randomGenerator;    
    _currentMoon = nullptr;
    std::cin.clear();
}


bool Game::getUserInput() {
    bool gameRunning = true;

    while (gameRunning && !_endGame) {
        std::string command;
        std::vector<std::string> args;

        std::cout << std::endl << "> ";
        std::getline(std::cin, command);
        util::splitArguments(command, args);
        util::lower(command);

        gameRunning = processCommand(command, args);
    }
    return false;
}

void Game::welcomeString() const {
    std::cout << DEADLY_CORP_TITLE << std::endl;
    std::cout << "Welcome! \nWe trust you will be a great asset to the corporation!\n" << std::endl;
}

bool Game::processCommand(const std::string& userCommand, std::vector<std::string>& args) {

    if (userCommand == "moons" || userCommand == "land" || userCommand == "leave"
        || userCommand == "store" || userCommand == "inventory" || userCommand == "exit") {

        if (!args.empty()) {
            std::cout << "\nUnknown command." << std::endl;
            return true;

        } else if (userCommand == "moons") {
            _moonManager->showMoons(*this);
            getUserInput();
            
        } else if (userCommand == "land") {
            if (_gamePhase == "Orbiting") {
                landOnMoon();
            } else {
                std::cout << "\nAlready landed on " << _currentMoon->name() << std::endl;
            }
            
        } else if (userCommand == "leave") {
            if (_gamePhase != "Landed") {
                std::cout << "\nThis command is not available at this time." << std::endl;

            } else {
                leaveMoon();
            }
      
        } else if (userCommand == "store") {
            _itemManager->showStoreItems(*this);
     
        } else if (userCommand == "inventory") {
            _itemManager->showInventory(*this);
        
        } else if (userCommand == "exit") {
            exit();
            return false; // Command to exit game
        }

        return true;
    
    } else if (userCommand == "route" || userCommand == "send" || userCommand == "buy"){
         
        if (userCommand == "route") {

            if (args.size() != 1) {
                std::cout << "\nBad command; the syntax is: 'route moonName'" << std::endl;
                return true;
            }

            util::lower(args[0]);
            std::string currentMoonName = _currentMoon->name();
            util::lower(currentMoonName);

            if (args[0] == currentMoonName) {
                std::cout << "\nAlready orbiting "<< _currentMoon->name() << std::endl;
                return true;
            
            } else if (_gamePhase == "Landed") {
                std::cout << "\nThis command is not available at this time." << std::endl;
                return true;
            }
            _moonManager->routeMoon(*this, args[0]);
        
        } else if (userCommand == "send") {

            if (args.size() != 1) {
                std::cout << "\nBad command; the syntax is: 'send numberOfEmployees'" << std::endl;
                return true;
            }
      
            try {
                int explorerCount = std::stoi(args[0]);

                if (explorerCount < 0) {
                    std::cout << "\nInvalid employee count '" << explorerCount << "'" << std::endl;
                    return true;
                }

                if (_gamePhase != "Landed") {
                    std::cout << "\nThis command is not available at this time." << std::endl;
                    return true;
                }

                if (_currentMoon->name() != "Corporation") {
                    if (explorerCount == 0) {
                        std::cout << "\nAt least one employee must be sent." << std::endl;
                        return true;
               
                    } else if (explorerCount > _aliveEmployees) {
                        std::cout << "\nOnly " << _aliveEmployees << " employees are left." << std::endl;
                        return true;
                    }
                }
                _currentMoon->sendEmployee(explorerCount, *this);
                
                if (_aliveEmployees == 0) {
                    leaveMoon();
                    return true;
                }
                           
            } catch (const std::invalid_argument& e) {
                std::cout << "\nInvalid amount '" << args[0] << "'" << std::endl;
            }
            
            return true;

        
        } else if (userCommand == "buy") {

            if (args.size() != 1) {
                std::cout << "\nBad command; the syntax is: 'buy itemName'" << std::endl;
                return true; 
            }

            util::lower(args[0]);
            _itemManager->buyItem(args[0], *this);
           
        }
        return true;
    
    } else if (userCommand == "sell") {

        if (_gamePhase == "Orbiting") {
            std::cout << "\nThis command is not available at this time." << std::endl;
            return true;
        }
        
        if (args.size() > 1) {
            std::cout << "\nBad command; the syntax is: 'sell optionalAmount'" << std::endl;
            return true;
        }

        else if (args.size() == 1) {
            try {
                int cargoSellValue = std::stoi(args[0]);
                if (cargoSellValue < 0) {
                    std::cout << "\nInvalid amount '" << args[0] << "'" << std::endl;

                } else {
                    _currentMoon->sellCargo(cargoSellValue, *this);
                }

            } catch (const std::invalid_argument& e) {
                std::cout << "\nInvalid amount '" << args[0] << "'" << std::endl;
            }
        
        } else {
            _currentMoon->sellCargo(_cargoValue, *this);
        }

        return true;
    
    } else {
        std::cout << "\nUnknown command." << std::endl;
        return true;
    };
}