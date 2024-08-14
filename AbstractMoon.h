#include <string>
#ifndef ABSTRACTMOON_H
#define ABSTRACTMOON_H


class Game;

enum class MoonWeather { Clear = 0, Flooded, Eclipsed, Stormy };

class AbstractMoon {

private:
    std::string _moonName;
    MoonWeather _moonWeather;

public:
    AbstractMoon(const std::string& moonName);

    virtual void onDayBegin(const Game& g) const;

    virtual void sendEmployee(const int& employeeCount, Game& g) =  0; 
    virtual void sellCargo(const int& value, Game& g) =  0;
    
    const std::string getWeather() const;
    const std::string& name() const;

    void setMoonWeather(MoonWeather weather);

};


#endif // MOONMANAGER_H