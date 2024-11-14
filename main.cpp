#include "inputmonitor.h"
#include "pieces.h"
#include "audio.h"
#include "graphics.h"
#include "main.h"
#include "pieceManager.h"

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
sf::Time currentTime;

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
    gameMain.setLevel(0);
    lockedBlocks.clear();
    gameMain.setGameStart(false);
    gameMain.setGameOver(false);
}
bool gameOverSoundPlayed = false;

int main()
{

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
        currentTime = gameClock.getElapsedTime();
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
            }
            else
            { // Check if clock is greater than preset "drop speed", if so, drop piece one block.
                pieceManager.dropPiece(gameClock, originPosition, lockedBlocks);
                // Draw falling piece.
                graphics.drawCurrentPiece(window, currentSprite, gameMain.getCurrentPiece(), originPosition, lockedBlocks);
                // Draw all locked pieces.
                graphics.drawLockedPieces(window, lockedBlocks, currentSprite);
            }
            // Draw area that displays next piece.
            window.draw(graphics.nextPieceArea());
            // Draw next piece.
            graphics.drawNextBlock(window, nextSprite, gameMain.getNextPiece());
            // Draw score/level area.
            window.draw(graphics.scoreArea());
            // Draw stats
            window.draw(graphics.stats());
        }
        else
        {
            // Flahses "Start Game" text on and off every 400ms.
            if (currentTime.asMilliseconds() >= 400)
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