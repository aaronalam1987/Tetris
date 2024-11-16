#include "graphics.h"
#include "pieces.h"
#include "main.h"
#include "pieceManager.h"

extern Graphics graphics;
extern Pieces pieces;
extern Main gameMain;
extern PieceManager pieceManager;

Graphics::Graphics()
{
    if (!font.loadFromFile("assets/font.ttf"))
    {
    }
}

// Load sprite asset for pieces.
sf::Sprite Graphics::loadBlock(std::string filename)
{
    texture.loadFromFile(filename);
    block.setTexture(texture);
    return block;
}

sf::Sprite Graphics::loadBG(std::string filename)
{
    texture2.loadFromFile(filename);
    bg.setTexture(texture2);
    return bg;
}

// Define our playfield.
sf::RectangleShape Graphics::playArea(int grid_width, int block_size, int grid_height)
{

    sf::RectangleShape playArea(sf::Vector2f(grid_width * block_size, grid_height * block_size));
    playArea.setFillColor(sf::Color(255, 255, 255, 128));
    playArea.setOutlineColor(sf::Color::Cyan);
    playArea.setOutlineThickness(2);

    // Set position to centre of window.
    playArea.setPosition((1024 - grid_width * block_size) / 2, 64);

    return playArea;
}

// Define the area which displays the next piece.
sf::RectangleShape Graphics::nextPieceArea()
{

    sf::RectangleShape nextPieceArea(sf::Vector2f(200, 200));
    nextPieceArea.setFillColor(sf::Color(255, 255, 255, 128));
    nextPieceArea.setOutlineColor(sf::Color::Cyan);
    nextPieceArea.setOutlineThickness(2);

    // Set position to the left of the play field.
    nextPieceArea.setPosition(80, 64);

    return nextPieceArea;
}

// Define the area which displays the next piece.
sf::RectangleShape Graphics::scoreArea()
{

    sf::RectangleShape scoreArea(sf::Vector2f(200, 200));
    scoreArea.setFillColor(sf::Color(255, 255, 255, 128));
    scoreArea.setOutlineColor(sf::Color::Cyan);
    scoreArea.setOutlineThickness(2);

    // Set position to the left of the play field.
    scoreArea.setPosition(744, 64);

    return scoreArea;
}

// Draw stat text (score/level).
sf::Text Graphics::stats()
{
    sf::Text stats;

    stats.setFont(font);
    stats.setString("Current Score:\n " + std::to_string(gameMain.getScore()) + "\n\n\n Current Level:\n " + std::to_string(gameMain.getLevel()));
    stats.setCharacterSize(24);
    stats.setFillColor(sf::Color::Black);
    stats.setStyle(sf::Text::Bold);

    // Set position within area on right of screen.
    stats.setPosition(754, 74);

    return stats;
}

// Draw start screen logo.
sf::RectangleShape Graphics::Logo(std::string filename)
{
    logo.loadFromFile(filename);
    sf::RectangleShape Logo(sf::Vector2f(672, 256));
    Logo.setTexture(&logo);
    Logo.setPosition((1024 - 672) / 2, 70);

    return Logo;
}

// Draw start screen text.
sf::Text Graphics::startGame()
{
    sf::Text start;

    start.setFont(font);
    start.setString("Press space to start");
    start.setCharacterSize(64);
    start.setFillColor(sf::Color::Black);
    start.setStyle(sf::Text::Bold);

    // Set position centre to screen.
    sf::FloatRect textBoundaries = start.getGlobalBounds();
    start.setPosition((1024 - textBoundaries.width) / 2, 600);
    return start;
}

// Draw game over text.
sf::Text Graphics::gameOver()
{
    sf::Text gameOver;

    gameOver.setFont(font);
    gameOver.setString("Game Over");
    gameOver.setCharacterSize(64);
    gameOver.setFillColor(sf::Color::Black);
    gameOver.setStyle(sf::Text::Bold);

    // Set position within area on right of screen.
    sf::FloatRect textBoundaries = gameOver.getGlobalBounds();
    gameOver.setPosition((1024 - textBoundaries.width) / 2, (768 - textBoundaries.height) / 2);

    return gameOver;
}

sf::Sprite Graphics::blockPiece()
{
    return block;
}

void Graphics::drawCurrentPiece(sf::RenderWindow &window, sf::Sprite &currentSprite, int cPiece, sf::Vector2i &originPosition, std::vector<BlockPosition> &lockedBlocks)
{
    auto block = pieces.currentBlock();
    if (block)
    {
        for (int i = 0; i < 4; i++)
        {
            // Check if we are trying to draw outside of playfield (which rotation can do), if so, move in a block.
            if (originPosition.x + block[i].x < 10)
            {
                originPosition.x += 1;
            }
            if (originPosition.x + block[i].x > 21)
            {
                originPosition.x -= 1;
            }
            if (originPosition.y + block[i].y > 21)
            {
                originPosition.y -= 1;
                pieceManager.pieceSettled(originPosition, lockedBlocks);
            }
            // Draw current shape from block sprite.
            currentSprite.setPosition((originPosition.x + block[i].x) * 32, (originPosition.y + block[i].y) * 32);
            currentSprite.setColor(pieces.getBlockColor(cPiece));
            window.draw(currentSprite);
        }
    }
}

void Graphics::drawNextBlock(sf::RenderWindow &window, sf::Sprite &nextSprite, int nPiece)
{
    auto blockNext = pieces.nextBlock(nPiece);
    if (blockNext)
    {
        // Calculate the center of the nextPieceArea.
        float nextPieceAreaX = 80;
        float nextPieceAreaY = 64;
        float nextPieceAreaWidth = 200;
        float nextPieceAreaHeight = 200;

        // Find the bounding box of the piece.
        int minX = blockNext[0].x, maxX = blockNext[0].x;
        int minY = blockNext[0].y, maxY = blockNext[0].y;

        for (int i = 1; i < 4; i++)
        {
            if (blockNext[i].x < minX)
                minX = blockNext[i].x;
            if (blockNext[i].x > maxX)
                maxX = blockNext[i].x;
            if (blockNext[i].y < minY)
                minY = blockNext[i].y;
            if (blockNext[i].y > maxY)
                maxY = blockNext[i].y;
        }

        // Calculate piece width and height in pixels.
        float pieceWidth = (maxX - minX + 1) * 32;
        float pieceHeight = (maxY - minY + 1) * 32;

        // Center position within the nextPieceArea.
        float centerX = nextPieceAreaX + (nextPieceAreaWidth - pieceWidth) / 2;
        float centerY = nextPieceAreaY + (nextPieceAreaHeight - pieceHeight) / 2;

        // Draw each block of the piece, offsetting by the bounding boxs top-left corner.
        for (int i = 0; i < 4; i++)
        {
            nextSprite.setPosition(
                centerX + (blockNext[i].x - minX) * 32,
                centerY + (blockNext[i].y - minY) * 32);
            nextSprite.setColor(pieces.getBlockColor(gameMain.getNextPiece()));
            window.draw(nextSprite);
        }
    }
}

void Graphics::drawLockedPieces(sf::RenderWindow &window, std::vector<BlockPosition> &lockedBlocks, sf::Sprite &sprite)
{
    for (const auto &pos : lockedBlocks)
    {
        sprite.setPosition(pos.x * 32, pos.y * 32);
        sprite.setColor(pieces.getBlockColor(pos.c));
        window.draw(sprite);
    }
}