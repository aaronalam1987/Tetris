#include "pieceManager.h"
#include "inputMonitor.h"
#include "pieces.h"
#include "main.h"
#include <iostream>

extern Main gameMain;
extern Audio audio;
extern Pieces pieces;
extern InputMonitor inputMonitor;
extern PieceManager pieceManager;

void PieceManager::checkGameEnd(std::vector<BlockPosition> &lockedBlocks)
{
    // Iterate through each block in the vector.
    for (const auto &pos : lockedBlocks)
    {
        // If any block is found with y == 2 (top of board), end the game.
        if (pos.y == 2)
        {
            // Set gameOver to true, play game over sound, exit loop.
            gameMain.setGameOver(true);
            audio.playSound(5);
            return;
        }
    }
}

void PieceManager::clearLines(int grid_width, std::vector<BlockPosition> &lockedBlocks)
{
    std::vector<int> rowBlockCount(22, 0); // Count blocks per row.

    // Count the blocks per row from the locked pieces.
    for (const auto &pos : lockedBlocks)
    {
        int rowIndex = pos.y; // Use the y-coordinate directly for the row.
        if (rowIndex >= 0 && rowIndex < 22)
        {
            rowBlockCount[rowIndex]++;
        }
    }

    std::vector<int> rowsToClear;

    // Store the total lines that are cleared.
    int totalLines = 0;
    // Store the total score to add.
    int scoreToAdd = 0;
    // Check which rows are full and need to be cleared.
    for (int y = 0; y < 22; ++y)
    {
        if (rowBlockCount[y] == grid_width)
        {
            // If the row is full, add to rowsToClear vector, increase score by 10 points.
            rowsToClear.push_back(y);
            // Increment score by 10 per line.
            scoreToAdd += 10;
            // After 10 cleared lines, if dropSpeed is greater than 100ms, reduce by 25ms per cleared line.
            if (gameMain.getDropSpeed() > 100 && gameMain.getScore() > 10)
            {
                gameMain.setDropSpeed(gameMain.getDropSpeed() - 25);
            }
            // Play piece cleared sound.
            audio.playSound(3);
            // Count up total lines to clear to calculate bonus score.
            totalLines += 1;
            // Add to totalLine count.
            gameMain.setTotalLines(gameMain.getTotalLines() + 1);
        }
    }

    // If there is score to add, create string for event text and add score.
    if (scoreToAdd != 0)
    {
        // Add additional points if more than 1 line is cleared at a time.
        int bonus = (totalLines == 2) ? 3 : (totalLines == 3) ? 5
                                        : (totalLines == 4)   ? 7
                                                              : 0;

        if (bonus > 0)
        {
            if (bonus == 3)
            {
                gameMain.setEventText("Double Line! +" + std::to_string(scoreToAdd + bonus) + "!");
            }
            if (bonus == 5)
            {
                gameMain.setEventText("Triple Line!! +" + std::to_string(scoreToAdd + bonus) + "!");
            }
            if (bonus == 7)
            {
                gameMain.setEventText("Quad Line!!! +" + std::to_string(scoreToAdd + bonus) + "!");
            }
        }
        else
        {
            // No bonus score thus only a single cleared line.
            gameMain.setEventText("Line Cleared! +10");
        }
        // Trigger event.
        gameMain.setIsEvent(true);
        // Increase current score.
        gameMain.setScore(gameMain.getScore() + scoreToAdd + bonus);
    }

    // Remove blocks in marked rows.
    for (const int y : rowsToClear)
    {
        lockedBlocks.erase(std::remove_if(lockedBlocks.begin(), lockedBlocks.end(),
                                          [y](const BlockPosition &pos)
                                          { return pos.y == y; }),
                           lockedBlocks.end());
    }

    // Shift blocks above down by one row.
    for (auto &pos : lockedBlocks)
    {
        for (int y : rowsToClear)
        {
            if (pos.y < y)
            {
                pos.y += 1;
            }
        }
    }
}

void PieceManager::checkInput(std::vector<BlockPosition> &lockedBlocks, sf::Vector2i &originPosition, sf::RenderWindow &window)
{
    int getInput = inputMonitor.monitorInput(window);

    switch (getInput)
    {
    case 1:
        if (originPosition.y <= gameMain.gridHeight() && !collisionCheck(pieces.currentBlock(), originPosition.x, originPosition.y + 1, lockedBlocks))
        {
            originPosition.y += 1;
        }
        else
        {
            // Piece has either hit another block or the bottom of the play field, call pieceSettled.
            pieceManager.pieceSettled(originPosition, lockedBlocks);
        }
        break;
    case 2:
        if (originPosition.x > 10 && !collisionCheck(pieces.currentBlock(), originPosition.x - 1, originPosition.y, lockedBlocks))
        {
            originPosition.x -= 1;
        }
        break;
    case 3:
        if (originPosition.x < 21 && !collisionCheck(pieces.currentBlock(), originPosition.x + 1, originPosition.y, lockedBlocks))
        {
            originPosition.x += 1;
        }
        break;
    }
}

// Check if the current piece collides with any previously locked blocks stored in vector.
bool PieceManager::collisionCheck(const sf::Vector2i block[], int originX, int originY, std::vector<BlockPosition> &lockedBlocks)
{
    for (int i = 0; i < 4; ++i)
    {
        int x = originX + block[i].x;
        int y = originY + block[i].y;
        for (const auto &pos : lockedBlocks)
        {
            if (pos.x == x && pos.y == y)
            {
                return true;
            }
        }
    }
    return false;
}

// Adds x y coordinates of locked piece to vector, vector is continually drawn and checked for rows.
void PieceManager::lockPiece(const sf::Vector2i block[], int originX, int originY, std::vector<BlockPosition> &lockedBlocks)
{
    for (int i = 0; i < 4; ++i)
    {
        int x = originX + block[i].x;
        int y = originY + block[i].y;
        lockedBlocks.push_back({x, y, gameMain.getCurrentPiece()});
    }
}

// Checks for elapsed time and drops piece to suit.
void PieceManager::dropPiece(sf::Clock &clock, sf::Vector2i &originPosition, std::vector<BlockPosition> &lockedBlocks)
{
    // Get elapsed time and compare to drop speed, if greater than or equal to, drop block one space and restart clock.
    if (clock.getElapsedTime().asMilliseconds() >= gameMain.getDropSpeed())
    {
        if (originPosition.y <= gameMain.gridHeight() && !collisionCheck(pieces.currentBlock(), originPosition.x, originPosition.y + 1, lockedBlocks))
        {
            clock.restart();
            // Check piece is within playField.
            if (originPosition.y <= gameMain.gridHeight())
            {
                originPosition.y += 1;
            }
        }
        else
        {
            // Piece has either hit another block or the bottom of the play field, call pieceSettled.
            pieceManager.pieceSettled(originPosition, lockedBlocks);
        }
    }
}

// Piece has settled (either at the bottom of play field or another piece) assign a new random piece.
void PieceManager::pieceSettled(sf::Vector2i &originPosition, std::vector<BlockPosition> &lockedBlocks)
{
    // Lockpiece by placing it's coordinates in the lockedBlocks array.
    pieceManager.lockPiece(pieces.currentBlock(), originPosition.x, originPosition.y, lockedBlocks);
    // Check if we have any lines to clear.
    pieceManager.clearLines(gameMain.gridWidth(), lockedBlocks);
    // Once piece is settled, check if it's touching the top of the game board.
    pieceManager.checkGameEnd(lockedBlocks);
    // Reset origin position for new block.
    originPosition.x = 16;
    originPosition.y = 3;
    // Set new current piece to "next" piece.
    gameMain.setCurrentPiece(gameMain.getNextPiece());
    // Set current block to new block.
    pieces.setCurrentBlock(gameMain.getCurrentPiece());
    pieces.newBlock(pieces.getCurrentBlock());
    // Set next piece to a random between 1-7 (this eventually becomes current piece).
    gameMain.setNextPiece(rand() % 7 + 1);
}

void PieceManager::gameEnd(std::vector<BlockPosition> &lockedBlocks)
{
    gameMain.setGameStart(false);
    gameMain.setGameOver(false);
    lockedBlocks.clear();
}