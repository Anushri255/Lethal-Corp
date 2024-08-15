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


//Getters
const int& Game::getBalance() const {
    return _balance;
}

const int& Game::getQuota() const {
    return _quota;
}

const int& Game::getCargoValue() const {
    return _cargoValue;
}

const ItemManager* Game::getItemManager() const {
    return _itemManager;
}

const int& Game::getAliveEmployees() const {
    return _aliveEmployees;
}

const int& Game::getDay() const {
    return _day;
}

const int& Game::getRemainingDays() const {
    return _remainingDays;
}

const AbstractMoon& Game::getCurrentMoon() const {
    return *_currentMoon;
}

RandomGenerator& Game::getRandomGenerator() const {
    return *_randomGenerator;
}


//Setters 

void Game::setAliveEmployees(const int& numOfEmployees) {
    _aliveEmployees = numOfEmployees;
}

void Game::setBalance(const int& updatedBalance)  {
    _balance = updatedBalance;
}

void Game::setCargoValue(const int& updatedCargoValue) {
    _cargoValue = updatedCargoValue;
}

void Game::setCurrentMoon(AbstractMoon* newMoon)  {
    _currentMoon = newMoon;
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

void Game::landOnMoon() {
    std::cout << "\n\nWELCOME to " << _currentMoon->name() << "!\n" << std::endl;
    std::cout << "Current cargo value: $" << _cargoValue << std::endl;
    std::cout << "Current balance: $" << _balance << std::endl;
    std::cout << "Current quota: $" << _quota << " (" << _remainingDays << " days left to meet quota)" << std::endl;
    std::cout << "Number of employees: " << _aliveEmployees << std::endl;

    if (_currentMoon->name() != "Corporation") {
        std::cout << "\nType SEND followed by the number of employees you wish to send inside the facility. All the other employees will stay on the ship. " << std::endl;
  
    } else {
        std::cout << "\nType SELL to sell your cargo contents and increase your balance and achieve quota." << std::endl;
        std::cout << "Specify the amount to sell after the SELL word to only sell a portion of your cargo." << std::endl;
    }
    std::cout << "Type LEAVE to leave the planet." << std::endl;

    _gamePhase = "Landed";

}

void Game::leaveMoon() {
    _day++;
    _moonManager->setMoonsWeather(*this);
    _remainingDays--;
    std::cout << "\n\n\n";
    _gamePhase = "Orbiting";
    _aliveEmployees = 4;

    if (_day % 4 == 1) {
        
        if (_balance >= _quota) {
            _quota = _quota + (_quota * 0.50);
            _remainingDays = 3;
            std::cout << "\n\n-------------------------------------" << std::endl;
            std::cout << "CONGRATULATIONS ON MAKING QUOTA!" << std::endl;
            std::cout << "New quota: $" << _quota << std::endl;
            std::cout << "-------------------------------------\n\n" << std::endl;
            _currentMoon->onDayBegin(*this);
        
        } else {
            std::cout << "\n\n------------------------------------" << std::endl;
            std::cout << ">>>>>>>>>>>>> GAME OVER <<<<<<<<<<<<" << std::endl;
            std::cout << "------------------------------------\n" << std::endl;
            std::cout << "You did not meet quota in time, and your employees have been fired." << std::endl;
            std::cout << "You kept them alive for " << _day - 1 << " days." << std::endl;
            _endGame = true;
            exit();

        }
    
    } else {
        _currentMoon->onDayBegin(*this);
    }
    
}

void Game::setupGame() {


    AbstractMoon* moon = new CorporationMoon("Corporation");
    _moonManager->registerMoon(moon);

    moon = new RegularMoons("Prototyping", 3, 30, 0.50);
    _moonManager->registerMoon(moon);

    moon = new RegularMoons("Insurance",5,50,0.45);
    _moonManager->registerMoon(moon);

    moon = new RegularMoons("Pledge", 30, 50, 0.40);
    _moonManager->registerMoon(moon);

    moon = new RegularMoons("Defence",10,70,0.35);
    _moonManager->registerMoon(moon);

    moon = new RegularMoons("April", 20, 120, 0.30,500);
    _moonManager->registerMoon(moon);

    moon = new RegularMoons("Tore", 100, 130, 0.25, 700);
    _moonManager->registerMoon(moon);

    moon = new RegularMoons("Hyperion", 100, 150, 0.20, 900);
    _moonManager->registerMoon(moon);

    for (AbstractMoon* moon : _moonManager->getMoonsList()) {
        if (moon->name() == "Corporation") {
            _currentMoon = moon;
            break;
        }    
    }
  
    Item* item = new Item("Flashlight", 60, 1,1.05, 1, 0, 0.5);
    _itemManager->registerItem(item);

    item = new Item("Shovel", 100, 1, 1.05, 1, 0, 0.5);
    _itemManager->registerItem(item);

    item = new Item("Pro-flashlight", 200, 1, 1.10, 1, 0, 0.5);
    _itemManager->registerItem(item);

    item = new Item("Teleporter", 300, 1, 1, 1, 0.33, 0.5);
    _itemManager->registerItem(item);

    item = new Item("Inverse-teleporter", 400, 1.10, 0.8, 1, 0, 0.5);
    _itemManager->registerItem(item);

    item = new Item("Backpack", 500, 1, 1, 1, 0, 1.25);
    _itemManager->registerItem(item);

    item = new Item("Hydraulics Mk2", 1000, 1, 1, 1.25, 0, 0.5);
    _itemManager->registerItem(item);

    _moonManager->setMoonsWeather(*this);

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