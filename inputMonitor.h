#ifndef INPUTMONITOR_H
#define INPUTMONITOR_H

#include <map>
#include <functional>
#include <SFML/Graphics.hpp>
enum keys{
    DOWN,
    LEFT,
    RIGHT,
    UP
};



class InputMonitor
{
private:
    

public:
    InputMonitor() {};

    int monitorInput(sf::RenderWindow &window);
    
};

#endif