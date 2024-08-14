#ifndef GAME_H
#define GAME_H

#include <string>
#include <random>

// Used AI to help format the deadly_corp_title
#define DEADLY_CORP_TITLE \
    "    ___               _ _           ___                 \n" \
    "   /   \\___  __ _  __| | |_   _    / __\\___  _ __ _ __  \n" \
    "  / /\\ / _ \\/ _` |/ _` | | | | |  / /  / _ \\| '__| '_ \\ \n" \
    " / /_//  __/ (_| | (_| | | |_| | / /__| (_) | |  | |_) |\n" \
    "/___,' \\___|\\__,_|\\__,_|_|\\__, | \\____/\\___/|_|  | .__/ \n" \
    "                          |___/                  |_|    "

class MoonManager;

class RandomGenerator;

class Game {

private:
    std::string _gamePhase;
    int _aliveEmployees;
    int _day;
    int _remainingDays;
    int _balance;
    int _quota;
    int _cargoValue;
    bool _endGame = false;
    RandomGenerator* _randomGenerator;
    AbstractMoon* _currentMoon;
    ItemManager* _itemManager;
    MoonManager* _moonManager;

public:

    Game();

    void setupGame();

    int startGame();

    void welcomeString() const;

    void landOnMoon();
    void leaveMoon();

    bool getUserInput();
    bool processCommand(const std::string& userCommand, std::vector<std::string>& args);

    void exit();

    const int& getBalance() const;
    const int& getQuota() const;
    const int& getCargoValue() const;
    const int& getAliveEmployees() const;
    const int& getDay() const;
    const int& getRemainingDays() const;
    RandomGenerator& getRandomGenerator() const;

    const ItemManager* getItemManager() const;
    const AbstractMoon& getCurrentMoon() const;

    void setBalance(const int& updatedBalance);
    void setCargoValue(const int& updatedCargoValue);
    void setAliveEmployees(const int& numOfEmployees);
    void setCurrentMoon(AbstractMoon* newMoon);


};

#endif // GAME_H
