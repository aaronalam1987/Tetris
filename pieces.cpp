#include "pieces.h"
extern Pieces pieces;

// Block definitions.
const sf::Vector2i LBlock[4] = {
    {0, 0},
    {0, -1},
    {0, -2},
    {1, 0}
};

const sf::Vector2i LineBlock[4] = {
    {0, 0},
    {0, -1},
    {0, 1},
    {0, 2}
};

const sf::Vector2i SqBlock[4] = {
    {0, 0},
    {0, 1},
    {1, 0},
    {1, 1}
};

const sf::Vector2i TBlock[4] = {
    {1, 0},
    {-1, 0},
    {0, -1},
    {0, 0}
};

const sf::Vector2i SBlock[4] = {
    {1, 0},
    {0, 0},
    {0, 1},
    {-1, 1}
};

sf::Vector2i tempPiece[4] = {
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0}
};

// Function to rotate pieces when space is pressed.
void Pieces::rotatePiece(){
    for(int i = 0; i < 4; i++){
        tempPiece[i] = {-tempPiece[i].y, tempPiece[i].x};
    }
}

// Function returns current block based on int input.
void Pieces::newBlock(int block){
    switch(block){
        case 1:
            for (int i = 0; i < 4; i++){
                tempPiece[i] = {LBlock[i].x, LBlock[i].y};
            }
            break;
        case 2:
        for (int i = 0; i < 4; i++){
                tempPiece[i] = {LineBlock[i].x, LineBlock[i].y};
            }
            break;
        case 3:
        for (int i = 0; i < 4; i++){
                tempPiece[i] = {SqBlock[i].x, SqBlock[i].y};
            }
            break;
        case 4:
        for (int i = 0; i < 4; i++){
                tempPiece[i] = {TBlock[i].x, TBlock[i].y};
            }
            break;
        case 5:
        for (int i = 0; i < 4; i++){
                tempPiece[i] = {SBlock[i].x, SBlock[i].y};
            }
            break;
    }

}

sf::Vector2i* Pieces::currentBlock(){
    return tempPiece;
}

const sf::Vector2i* Pieces::nextBlock(int block){
    switch(block){
        case 1:
            return LBlock;
        case 2:
            return LineBlock;
        case 3:
            return SqBlock;
        case 4:
            return TBlock;
        case 5:
            return SBlock;
        default:
            return nullptr;
    }
}

sf::Color Pieces::getBlockColor(int c){
    switch(c){
        case 1:
            return sf::Color::White;
        case 2:
            return sf::Color::Green;
        case 3:
            return sf::Color::Blue;
        case 4:
            return sf::Color::Red;
        case 5:
            return sf::Color::Yellow;
        default:
            return sf::Color::White;
    }
}