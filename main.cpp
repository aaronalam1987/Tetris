#include "inputmonitor.h"
#include "pieces.h"
#include "global.h"
#include "audio.h"
#include "graphics.h"
#include "main.h"
#include "pieceManager.h"

#include <SFML/System/Clock.hpp>
#include <time.h>
#include <vector>

sf::Event event;
sf::RenderWindow window(sf::VideoMode(1024, 768, 32), "Tetris", sf::Style::Default);
sf::Sprite currentSprite;
sf::Sprite background;
sf::Vector2i originPosition(16, 4); 
sf::Sprite nextSprite;
sf::Clock gameClock;

Audio audio;
Graphics graphics;
InputMonitor inputMonitor;
Pieces pieces;
Main home;
PieceManager pieceManager;

// x, y position and c for color.
std::vector<BlockPosition> lockedBlocks;

int main()
{   
    // Play BGM (from audio.cpp)
    audio.playBGM();
    
    // srand seed for random number.
    srand(time(NULL));    
    
    // nPiece array holds a random number between 1-4, [0] is current piece, [1] is next piece.
    home.setCurrentPiece(rand() % 5 + 1);
    home.setNextPiece(rand() % 5 + 1);

    // Set initial block to newly generated random number between 1-4.
    pieces.setCurrentBlock(home.getCurrentPiece());
    pieces.newBlock(pieces.getCurrentBlock());

    // Cap framerate to 60fps because you know.. who needs more than 60fps for Tetris =)
    window.setFramerateLimit(60);

    // Load block sprite.
    background = graphics.loadBG("assets/graphics/BG.png");
    currentSprite = graphics.loadBlock("assets/graphics/blockPiece.png");
    nextSprite = graphics.loadBlock("assets/graphics/blockPiece.png");

    // Main game loop
    while (window.isOpen())
    {
        // Clear display
        window.clear();
        // Check if clock is greater than preset "drop speed", if so, drop piece one block.
        pieceManager.dropPiece(gameClock, originPosition, lockedBlocks);

        // Check for events.
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            // Checks for input and out of bounds blocks.
            pieceManager.checkInput(lockedBlocks, originPosition);
        }

        // Set up our game window, clear window, draw associated block by looping through array, display sprites.
        window.draw(background);
        // Draw area that displays next piece.
        window.draw(graphics.nextPieceArea());
        // Draw score/level area.
        window.draw(graphics.scoreArea());
        // Draw stats
        window.draw(graphics.stats());
        // Draw playfield.
        window.draw(graphics.playArea(home.gridWidth(), home.blockSize(), home.gridHeight()));
        // Draw next piece.void Graphics::drawNextBlock(sf::RenderWindow &window, sf::Sprite &spriteNext, int nPiece){
        graphics.drawNextBlock(window, nextSprite, home.getNextPiece());
        // Draw falling piece.
        graphics.drawCurrentPiece(window, currentSprite, home.getCurrentPiece(), originPosition, lockedBlocks);
        // Draw all locked pieces.
        graphics.drawLockedPieces(window, lockedBlocks, currentSprite);
        // Display everything.
        window.display();
    }
    return 0;
}