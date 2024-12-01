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
    int compareHighScore();
    void createNewHighScores();
    void updateHighScores(int pos);
    std::string getHighScoreName() { return highscoreName; }
    void updateHighScoreName(std::string name) { highscoreName = name; }
    void popBackHighScoreName()
    {
        if (!highscoreName.empty())
        {
            highscoreName.pop_back();
        }
    }

private:
    json jsonHighScore;
    std::string highscoreName;
};

#endif