#ifndef ROTATION_H
#define ROTATION_H

#include "global.h"

extern sf::Vector2i LBlock[4];
extern sf::Vector2i LineBlock[4];
extern sf::Vector2i SqBlock[4];
extern sf::Vector2i TBlock[4];
extern sf::Vector2i SBlock[4];
extern sf::Vector2i tempPiece[4];

class Pieces
{
    private:
    int cBlock;

    public:
    Pieces(){};

    sf::Vector2i* currentBlock();
    void newBlock(int block);
    const sf::Vector2i* Pieces::nextBlock(int block);
    void rotatePiece();
    sf::Color getBlockColor(int c);

    int getCurrentBlock()
    {
        return cBlock;
    }
    void setCurrentBlock(int currBlock)
    {
        cBlock = currBlock;
    }

};

#endif