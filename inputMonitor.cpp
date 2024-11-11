#include "global.h"
#include "inputMonitor.h"
#include "pieces.h"
#include "audio.h"

extern sf::Event event;
extern Pieces pieces;
extern Audio audio;
extern InputMonitor inputMonitor;

int key = 4;

int InputMonitor::monitorInput(){
    
    //Define a map for sf::Keyboard::key to function method.
    std::map<sf::Keyboard::Key, std::function<void()>> keyActions;

    keyActions[sf::Keyboard::Space] = [&]()
    { pieces.rotatePiece(); audio.playSound(1); };

     keyActions[sf::Keyboard::Down] = [&]()
    { audio.playSound(2); key = 1; };

    keyActions[sf::Keyboard::Left] = [&]()
    { key = 2; };

    keyActions[sf::Keyboard::Right] = [&]()
    { key = 3; };

    // Check for corresponding key action function on sf::Event::KeyPressed.
    if (event.type == sf::Event::KeyPressed)
    {
        auto findKey = keyActions.find(event.key.code);
        if (findKey != keyActions.end())
        {
            findKey -> second();
        }
    }
    int returnKey = key;
    key = 4;
    return returnKey;
}