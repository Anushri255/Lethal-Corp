#ifndef MOONMANAGER_H
#define MOONMANAGER_H

#include "AbstractMoon.h"
#include <vector>

class Game;

class MoonManager {

private:
    std::vector<AbstractMoon*> _moonsList;

public:
    MoonManager();
    ~MoonManager();

    void registerMoon(AbstractMoon* moon);

    void showMoons(const Game& g) const;

    void routeMoon(Game& g, const std::string& moonName);

    void setMoonsWeather(Game& g);

    const std::vector<AbstractMoon*>& getMoonsList() const;

};
#endif // MOONMANAGER_H