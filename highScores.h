#ifndef HIGHSCORES_H
#define HIGHSCORES_H

#include "nlohmann/json.hpp"
#include <iostream>
using json = nlohmann::json;

class highScores
{
    public:
        std::string getHighScores();
        void loadHighScores();
        bool compareHighScore();
        void createNewHighScores();
        void updateHighScores(int pos, std::string name);


    private:
        json jsonHighScore;
};

#endif