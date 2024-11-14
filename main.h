#ifndef MAIN_H
#define MAIN_H
#include <SFML/Graphics.hpp>

struct BlockPosition
{
    int x = 0;
    int y = 0;
    int c = 0;
};

class Main
{
private:
    const int grid_width = 12;
    const int grid_height = 20;
    const int block_size = 32;
    int nPiece[2] = {0};
    int dropSpeed = 2000;
    int score = 0;
    int level = 0;
    bool doRotate = true;
    bool gameStart = false;
    bool showStartText = true;
    bool gameOver = false;

public:
    Main() = default;
    // Game logic specific.
    void pieceSettled();

    // Grid dimensions.
    int gridWidth() const { return grid_width; }
    int gridHeight() const { return grid_height; }

    // Block size.
    int blockSize() const { return block_size; }

    // Piece management.
    int getCurrentPiece() const { return nPiece[0]; }
    void setCurrentPiece(int piece) { nPiece[0] = piece; }
    int getNextPiece() const { return nPiece[1]; }
    void setNextPiece(int piece) { nPiece[1] = piece; }

    // Gameplay specifics.
    int getDropSpeed() const { return dropSpeed; }
    void setDropSpeed(int speed) { dropSpeed = speed; }
    int getLevel() const { return level; }
    void setLevel(int l) { level = l; }
    int getScore() const { return score; }
    void setScore(int sc) { score = sc; }
    int getGameOver() { return gameOver; }
    void setGameOver(bool game){ gameOver = game; }

    // Rotation flags.
    bool getDoRotate() { return doRotate; }
    void setRotate(bool rotate) { doRotate = rotate; }

    bool getGameStart() { return gameStart; }
    void setGameStart(bool start) { gameStart = start; }

    // Graphics specific.
    bool getShowStartText() { return showStartText; }
    void setShowStartText(bool show) { showStartText = show; }

    void resetGame();
};
#endif