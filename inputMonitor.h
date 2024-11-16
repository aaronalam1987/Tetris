#ifndef INPUTMONITOR_H
#define INPUTMONITOR_H

#include <map>
#include <functional>
#include <SFML/Graphics.hpp>

// Definitions for keys.
enum keys
{
    NA,
    DOWN,
    LEFT,
    RIGHT
};

class InputMonitor
{
private:
public:
    InputMonitor() = default;

    int monitorInput(sf::RenderWindow &window);
};

#endif