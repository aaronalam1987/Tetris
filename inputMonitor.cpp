#include "inputMonitor.h"
#include "pieces.h"
#include "audio.h"
#include "main.h"
#include "highscores.h"

extern sf::Event event;
extern Pieces pieces;
extern Audio audio;
extern InputMonitor inputMonitor;
extern Main gameMain;
extern highScores highscores;

int key = 4;
keys Keys;

void InputMonitor::enterHighScore()
{
    if (event.type == sf::Event::TextEntered)
    {
        char enteredChar = static_cast<char>(event.text.unicode);
        // Return key pressed, update highscores.
        if (enteredChar == '\r')
        {
            // Force name entry.
            if (highscores.getHighScoreName().length() > 0)
            {
                // Update highscores with the value returned by compareHighScore (which gives us the position to replace) we could instead
                // pass the value given from when we previously checked but this is simple and works.
                highscores.updateHighScores(highscores.compareHighScore());
                gameMain.setHighScores(highscores.getHighScores());
                gameMain.resetGame();
            }
        }
        if (event.text.unicode < 128)
        {
            if (enteredChar != '\r')
            {
                if (highscores.getHighScoreName().length() <= 9)
                {
                    // Append highscore name.
                    highscores.updateHighScoreName(highscores.getHighScoreName() += enteredChar);
                }
            }
        }
    }
}

int InputMonitor::monitorInput(sf::RenderWindow &window)
{

    // Define a map for sf::Keyboard::key to function method.
    std::map<sf::Keyboard::Key, std::function<void()>> keyActions;

    // Check if rotation flag is true, if so, rotate piece and set to false (stops spamming rotation).
    keyActions[sf::Keyboard::Space] = [&]()
    {
        // Check if gameOver flag isn't true.
        if (!gameMain.getGameOver())
        {
            // Check if gameStart flag is true.
            if (gameMain.getGameStart())
            {
                // Check if "doRotate" is true which is set when space key is lifted.
                if (gameMain.getDoRotate())
                {
                    // Don't allow rotate or sound for square block as this is unnecessary (block can be rotated and looks stupid otherwise).
                    if (pieces.getCurrentBlock() != 3)
                    {
                        pieces.rotatePiece();
                        audio.playSound(1);
                        // Set "doRotate" to false, this is to stop infinite rotation and requires lifting space key to flag to true.
                        gameMain.setRotate(false);
                    }
                }
            }
            else
            {
                // Game hasn't started, play "start" sound and set gamestart to true.
                audio.playSound(4);
                gameMain.setGameStart(true);
            }
        }
        else
        { // gameOver flag is true, space is pressed - call reset game.
            gameMain.resetGame();
        }
    };

    // Only accept input if game is running (gameOver flag not true).
    if (!gameMain.getGameOver())
    {
        keyActions[sf::Keyboard::Down] = [&]()
        { audio.playSound(2); key = 1; };

        keyActions[sf::Keyboard::Left] = [&]()
        { key = 2; };

        keyActions[sf::Keyboard::Right] = [&]()
        { key = 3; };
    }

    keyActions[sf::Keyboard::Escape] = [&]()
    { window.close(); };

    // Check for corresponding key action function on sf::Event::KeyPressed.
    if (event.type == sf::Event::KeyPressed)
    {
        auto findKey = keyActions.find(event.key.code);
        if (findKey != keyActions.end())
        {
            findKey->second();
        }
    }

    // Check if space has been lifted, allow rotation.
    if (event.type == sf::Event::KeyReleased)
    {
        if (sf::Keyboard::Space)
        {
            gameMain.setRotate(true);
        }
    }
    int returnKey = key;
    key = 4;
    return returnKey;
}