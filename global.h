#ifndef GLOBAL_H
#define GLOBAL_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
extern sf::Vector2i originPosition; 
struct BlockPosition {
    int x;
    int y;
    int c;
};
#endif