#include "graphics.h"
#include "pieces.h"
#include "main.h"
#include "pieceManager.h"

extern Graphics graphics;
extern Pieces pieces;
extern Main home;
extern PieceManager pieceManager;

Graphics::Graphics(){
    if(!font.loadFromFile("assets/font.ttf")){
        std::cout << "Error loading font." << std::endl;
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
sf::RectangleShape Graphics::playArea(int grid_width, int block_size, int grid_height){

    sf::RectangleShape playArea(sf::Vector2f(grid_width * block_size, grid_height * block_size));
    playArea.setFillColor(sf::Color(255,255,255,128));
    playArea.setOutlineColor(sf::Color::Cyan);
    playArea.setOutlineThickness(2);

    // Set position to centre of window.
    playArea.setPosition((1024 - grid_width * block_size) / 2, 64);

    return playArea;
}

// Define the area which displays the next piece.
sf::RectangleShape Graphics::nextPieceArea(){

    sf::RectangleShape nextPieceArea(sf::Vector2f(200, 200));
    nextPieceArea.setFillColor(sf::Color(255,255,255,128));
    nextPieceArea.setOutlineColor(sf::Color::Cyan);
    nextPieceArea.setOutlineThickness(2);

    // Set position to the left of the play field.
    nextPieceArea.setPosition(80, 64);

    return nextPieceArea;
}

// Define the area which displays the next piece.
sf::RectangleShape Graphics::scoreArea(){

    sf::RectangleShape scoreArea(sf::Vector2f(200, 200));
    scoreArea.setFillColor(sf::Color(255,255,255,128));
    scoreArea.setOutlineColor(sf::Color::Cyan);
    scoreArea.setOutlineThickness(2);

    // Set position to the left of the play field.
    scoreArea.setPosition(744, 64);

    return scoreArea;
}

// Draw stat text (score/level)
sf::Text Graphics::stats(){
    sf::Text stats;

    stats.setFont(font);
    stats.setString("Current Score: \n " + std::to_string(home.getScore()) + "\n\n\n Current Level:\n" + std::to_string(home.getLevel()));
    stats.setCharacterSize(24);
    stats.setFillColor(sf::Color::Black);
    stats.setStyle(sf::Text::Bold);

    // Set position within area on right of screen.
    stats.setPosition(754, 74);

    return stats;
}

// Draw stat text (score/level)
sf::Text Graphics::startGame(){
    sf::Text stats;

    stats.setFont(font);
    stats.setString("Press space to start");
    stats.setCharacterSize(64);
    stats.setFillColor(sf::Color::Black);
    stats.setStyle(sf::Text::Bold);

    // Set position centre to screen.
    sf::FloatRect textBoundaries = stats.getGlobalBounds();
    stats.setPosition((1024 - textBoundaries.width) / 2, (768 - textBoundaries.height) / 2);
    return stats;
}

sf::Sprite Graphics::blockPiece(){
    return block;
}

void Graphics::drawCurrentPiece(sf::RenderWindow &window, sf::Sprite &currentSprite, int cPiece, sf::Vector2i &originPosition, std::vector<BlockPosition> &lockedBlocks){
    auto block = pieces.currentBlock();
    if(block){
        for(int i = 0; i < 4; i++){
            // Check if we are trying to draw outside of playfield (which rotation can do), if so, move in a block.

            if(originPosition.x + block[i].x < 10){
                originPosition.x += 1;
                }
                if(originPosition.x + block[i].x > 21){
                    originPosition.x -= 1;
                }
                if(originPosition.y + block[i].y > 21){
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

void Graphics::drawNextBlock(sf::RenderWindow &window, sf::Sprite &nextSprite, int nPiece){
    auto blockNext = pieces.nextBlock(nPiece);
    if(blockNext){
        for (int i = 0; i < 4; i++){
            nextSprite.setPosition((4 + blockNext[i].x) * 32, (4 + blockNext[i].y) * 32);
            window.draw(nextSprite);
            }
        }
}

void Graphics::drawLockedPieces(sf::RenderWindow &window, std::vector<BlockPosition> &lockedBlocks, sf::Sprite &sprite){
    for (const auto& pos : lockedBlocks) {
            sprite.setPosition(pos.x * 32, pos.y * 32);
            sprite.setColor(pieces.getBlockColor(pos.c));
            window.draw(sprite);
        }
}