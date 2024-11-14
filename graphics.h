#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "main.h"

class Graphics
{
public:
    Graphics();
    sf::RectangleShape Logo(std::string filename);
    sf::Sprite loadBlock(std::string filename);
    sf::Sprite loadBG(std::string filename);
    sf::Sprite blockPiece();
    sf::RectangleShape playArea(int grid_width, int block_size, int grid_height);
    sf::RectangleShape nextPieceArea();
    sf::RectangleShape scoreArea();
    sf::Text stats();
    sf::Text startGame();
    sf::Text gameOver();
    void drawLockedPieces(sf::RenderWindow &window, std::vector<BlockPosition> &lockedBlocks, sf::Sprite &sprite);
    void drawCurrentPiece(sf::RenderWindow &window, sf::Sprite &currentSprite, int cPiece, sf::Vector2i &originPosition, std::vector<BlockPosition> &lockedBlocks);
    void drawNextBlock(sf::RenderWindow &window, sf::Sprite &nextSprite, int nPiece);

private:
    sf::Font font;
    sf::Texture texture;
    sf::Texture texture2;
    sf::Texture logo;
    sf::Sprite block;
    sf::Sprite bg;
};

#endif