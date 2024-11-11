#include "pieceManager.h"
#include "inputMonitor.h"
#include "pieces.h"
#include "main.h"

extern Main home;
extern Audio audio;
extern Pieces pieces;
extern InputMonitor inputMonitor;
extern PieceManager pieceManager;

void PieceManager::clearLines(int grid_width, std::vector<BlockPosition> &lockedBlocks) {
    std::vector<int> rowBlockCount(22, 0); // Count blocks per row

    // Count the blocks per row from the locked pieces
    for (const auto& pos : lockedBlocks) {
        int rowIndex = pos.y;  // Use the y-coordinate directly for the row
        if (rowIndex >= 0 && rowIndex < 22) {
            rowBlockCount[rowIndex]++;
        }
    }

    // Track rows that are full and need clearing
    std::vector<int> rowsToClear;

    // Check which rows are full and need to be cleared
    for (int y = 0; y < 22; ++y) {
        if (rowBlockCount[y] == grid_width) {  // If the row is full
            rowsToClear.push_back(y);
            home.setScore((home.getScore() +1));
             audio.playSound(3);
        }
    }

    // Remove blocks in marked rows (remove after determining all rows to clear)
    for (const int y : rowsToClear) {
        lockedBlocks.erase(std::remove_if(lockedBlocks.begin(), lockedBlocks.end(),
                                          [y](const BlockPosition& pos) { return pos.y == y; }),
                           lockedBlocks.end());
    }

    // Shift blocks above down by one row
    for (auto& pos : lockedBlocks) {
        for (int y : rowsToClear) {
            if (pos.y < y) {  // If the block is above the cleared row, shift it down
                pos.y += 1;
            }
        }
    }
}

void PieceManager::checkInput(std::vector<BlockPosition> &lockedBlocks, sf::Vector2i &originPosition){
    int getInput = inputMonitor.monitorInput();
    switch(getInput){
        case 1:
        if (originPosition.y <= home.gridHeight() && !collisionCheck(pieces.currentBlock(), originPosition.x, originPosition.y + 1, lockedBlocks)) {
            originPosition.y += 1;
            }
            else {
                // Piece has either hit another block or the bottom of the play field, call pieceSettled.
                pieceManager.pieceSettled(originPosition, lockedBlocks);
            }
            break;
        case 2:
        if (originPosition.x > 10 && !collisionCheck(pieces.currentBlock(), originPosition.x - 1, originPosition.y, lockedBlocks)) {
            originPosition.x -= 1;
            }
            break;
        case 3:
        if (originPosition.x < 21 && !collisionCheck(pieces.currentBlock(), originPosition.x + 1, originPosition.y, lockedBlocks)) {
            originPosition.x += 1;
            }
            break;
    }
}

// Check if the current piece collides with any previously locked blocks stored in vector.
bool PieceManager::collisionCheck(const sf::Vector2i block[], int originX, int originY, std::vector<BlockPosition> &lockedBlocks) {
    for (int i = 0; i < 4; ++i) {
        int x = originX + block[i].x;
        int y = originY + block[i].y;
        for (const auto& pos : lockedBlocks) {
            if (pos.x == x && pos.y == y) {
                return true;
            }
        }
    }
    return false;
}

// Adds x y coordinates of locked piece to vector, vector is continually drawn and checked for rows.
void PieceManager::lockPiece(const sf::Vector2i block[], int originX, int originY, std::vector<BlockPosition> &lockedBlocks) {
    for (int i = 0; i < 4; ++i) {
        int x = originX + block[i].x;
        int y = originY + block[i].y;
        lockedBlocks.push_back({x, y, home.getCurrentPiece()});
    }
}

// Checks for elapsed time and drops piece to suit. 
void PieceManager::dropPiece(sf::Clock& clock, sf::Vector2i &originPosition, std::vector<BlockPosition> &lockedBlocks){
    // Get elapsed time and compare to drop speed, if greater than or equal to, drop block one space and restart clock.
    if (clock.getElapsedTime().asMilliseconds() >= home.getDropSpeed()) {
        clock.restart();
        // Check piece is within playField.
        if (originPosition.y < home.gridHeight()- 1) {
            originPosition.y += 1;
        } 
        else {
            pieceManager.pieceSettled(originPosition, lockedBlocks);
        }
    }
}

// Piece has settled (either at the bottom of play field or another piece) assign a new random piece. 
void PieceManager::pieceSettled(sf::Vector2i &originPosition, std::vector<BlockPosition> &lockedBlocks){
    // Lockpiece by placing it's coordinates in the lockedBlocks array.
    pieceManager.lockPiece(pieces.currentBlock(), originPosition.x, originPosition.y, lockedBlocks);
    // Check if we have any lines to clear.
    pieceManager.clearLines(home.gridWidth(), lockedBlocks);
    // Reset origin position for new block.
    originPosition.x = 16;
    originPosition.y = 4;
    // Set new current piece to "next" piece.
    home.setCurrentPiece(home.getNextPiece());
    // Set current block to new block.
    pieces.setCurrentBlock(home.getCurrentPiece());
    pieces.newBlock(pieces.getCurrentBlock());
    // Set next piece to a random between 1-4 (this eventually becomes current piece).
    home.setNextPiece(rand() % 5 + 1);
}