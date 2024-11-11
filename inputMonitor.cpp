#include "global.h"
#include "inputMonitor.h"
#include "pieces.h"
#include "audio.h"
#include "main.h"

extern sf::Event event;
extern Pieces pieces;
extern Audio audio;
extern InputMonitor inputMonitor;
extern Main home;

int key = 4;

int InputMonitor::monitorInput(){
    
    //Define a map for sf::Keyboard::key to function method.
    std::map<sf::Keyboard::Key, std::function<void()>> keyActions;

    // Check if rotation flag is true, if so, rotate piece and set to false (stops spamming rotation).
    keyActions[sf::Keyboard::Space] = [&]()
    { if(home.getGameStart()){ if(home.getDoRotate()){ pieces.rotatePiece(); audio.playSound(1); home.setRotate(false);} } else { audio.playSound(4); home.setGameStart(true);}};

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

    // Check if space has been lifted, allow rotation.
    if(event.type == sf::Event::KeyReleased){
        if(sf::Keyboard::Space){
            home.setRotate(true);
        }
    }
    int returnKey = key;
    key = 4;
    return returnKey;
}