#ifndef PIECEMANAGER_H
#define PIECEMANAGER_H

#include "main.h"
#include "audio.h"

class PieceManager{
    public:
        void clearLines(int grid_width, std::vector<BlockPosition> &lockedBlocks);
        void checkInput(std::vector<BlockPosition> &lockedBlocks, sf::Vector2i &originPosition);
        bool collisionCheck(const sf::Vector2i block[], int originX, int originY, std::vector<BlockPosition> &lockedBlocks);
        void lockPiece(const sf::Vector2i block[], int originX, int originY, std::vector<BlockPosition> &lockedBlocks);
        void dropPiece(sf::Clock& clock, sf::Vector2i &originPosition, std::vector<BlockPosition> &lockedBlocks);
        void pieceSettled(sf::Vector2i &originPosition, std::vector<BlockPosition> &lockedBlocks);
};

#endif