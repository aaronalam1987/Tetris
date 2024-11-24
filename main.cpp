#include "inputmonitor.h"
#include "pieces.h"
#include "audio.h"
#include "graphics.h"
#include "main.h"
#include "pieceManager.h"
#include "highScores.h"
#include <iostream>
#include <SFML/System/Clock.hpp>
#include <time.h>
#include <vector>

sf::Event event;
sf::RenderWindow window(sf::VideoMode(1024, 768, 32), "Tetris", sf::Style::Close);
sf::Sprite currentSprite;
sf::Sprite background;
sf::RectangleShape Logo;
sf::Vector2i originPosition(16, 3);
sf::Sprite nextSprite;
sf::Clock gameClock;
sf::Clock eventClock;

highScores highscores;
Audio audio;
Graphics graphics;
InputMonitor inputMonitor;
Pieces pieces;
Main gameMain;
PieceManager pieceManager;

// x, y position and c for color.
std::vector<BlockPosition> lockedBlocks;

void Main::resetGame()
{
    // Reset everything for new game.
    audio.playBGM();
    gameMain.setDropSpeed(2000);
    gameMain.setScore(0);
    gameMain.setTotalLines(0);
    lockedBlocks.clear();
    gameMain.setEventText("");
    gameMain.setGameStart(false);
    gameMain.setGameOver(false);
}
bool gameOverSoundPlayed = false;

int main()
{
    if (gameMain.getLoadHighScores())
    {
        gameMain.setHighScores(highscores.getHighScores());
        gameMain.setLoadHighScores(false);
    }
    // Play BGM (from audio.cpp)
    audio.playBGM();
    audio.loadAudio();

    // srand seed for random number.
    srand(time(NULL));

    // Set current piece and next piece to a random value between 1-7.
    gameMain.setCurrentPiece(rand() % 7 + 1);
    gameMain.setNextPiece(rand() % 7 + 1);

    // Set initial block to newly generated piece.
    pieces.setCurrentBlock(gameMain.getCurrentPiece());
    pieces.newBlock(pieces.getCurrentBlock());

    // Cap framerate to 60fps because you know.. who needs more than 60fps for Tetris =)
    window.setFramerateLimit(60);

    // Load block sprite.
    background = graphics.loadBG("assets/graphics/BG.png");
    currentSprite = graphics.loadBlock("assets/graphics/blockPiece.png");
    nextSprite = graphics.loadBlock("assets/graphics/blockPiece.png");
    Logo = graphics.Logo("assets/graphics/Logo.png");

    // Main game loop
    while (window.isOpen())
    {
        highscores.compareHighScore();
        // Clear display
        window.clear();
        // Check for events.
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            // Checks for input and out of bounds blocks.
            pieceManager.checkInput(lockedBlocks, originPosition, window);
        }

        // Set up our game window, clear window, draw associated block by looping through array, display sprites.
        window.draw(background);

        if (gameMain.getGameStart())
        {
            // Draw playfield.
            window.draw(graphics.playArea(gameMain.gridWidth(), gameMain.blockSize(), gameMain.gridHeight()));
            //  If game is over, draw entire play screen but do not drop piece, do not draw locked blocks and show "game over" text.
            if (gameMain.getGameOver())
            {
                // game over here
                audio.stopBGM();
                if (!gameOverSoundPlayed)
                {
                    audio.playSound(5);
                    gameOverSoundPlayed = true; // Set the flag so the sound only plays once
                }
                window.draw(graphics.gameOver());

                // Check if there is a new highscore.
                if (highscores.compareHighScore())
                {
                    gameMain.setEventText("New Highscore!");
                    gameMain.setIsEvent(true);

                    // TO BE IMPLEMENTED.
                }
            }
            else
            { // Check if clock is greater than preset "drop speed", if so, drop piece one block.
                pieceManager.dropPiece(gameClock, originPosition, lockedBlocks);
                // Draw falling piece.
                graphics.drawCurrentPiece(window, currentSprite, gameMain.getCurrentPiece(), originPosition, lockedBlocks);
                // Draw all locked pieces.
                graphics.drawLockedPieces(window, lockedBlocks, currentSprite);
            }
            // Check for game events ("Lined Cleared! etc")
            // Keep event clock reset unless there is an event, otherwise clock will exceed event duration and when an event is triggered, immediately reset causing text to only flash.
            if (!gameMain.getIsEvent())
            {
                eventClock.restart();
            }
            else
            {
                // Draw the event text.
                window.draw(graphics.eventText(gameMain.getEventText()));
                // Check if 2 seconds have passed.
                if (eventClock.getElapsedTime().asSeconds() >= 2)
                {
                    gameMain.setIsEvent(false);
                    eventClock.restart();
                }
            }
            // Draw area that displays next piece.
            window.draw(graphics.nextPieceArea());
            // Draw area that displays global highscores.
            window.draw(graphics.highScores());
            // Draw global highscores text.
            window.draw(graphics.highScoreText());
            // Draw next piece.
            graphics.drawNextBlock(window, nextSprite, gameMain.getNextPiece());
            // Draw score/level area.
            window.draw(graphics.scoreArea());
            // Draw stats
            window.draw(graphics.stats());
        }
        else
        {
            // Flashes "Start Game" text on and off every 400ms.
            // We can reuse gameClock here as this only affects when no game is running.
            if (gameClock.getElapsedTime().asMilliseconds() >= 400)
            {
                gameClock.restart();
                gameMain.getShowStartText() == true ? gameMain.setShowStartText(false) : gameMain.setShowStartText(true);
            }
            if (gameMain.getShowStartText())
            {
                window.draw(graphics.startGame());
            }
            window.draw(Logo);
        }
        // Display everything.
        window.display();
    }
    return 0;
}