#include "highScores.h"
#include "main.h"
#include <fstream>
#include <iostream>

extern highScores highscores;
extern Main gameMain;

void highScores::loadHighScores()
{
    if (std::filesystem::exists("scores.json"))
    {
        highscores.getHighScores();
    }
    else
    {
        createNewHighScores();
    }
}

void highScores::updateHighScores(int pos, std::string name)
{
    // Open scores file.
    std::ifstream inputFile("scores.json");

    if (!inputFile.is_open())
    {
        std::cout << "Failed to load scores.json" << std::endl;
    }
    else
    {
        try
        {
            // Parse the JSON.
            json jsonHighScore = json::parse(inputFile);
            jsonHighScore[pos]["score"] = gameMain.getScore();
            jsonHighScore[pos]["name"] = name;

            // Save the updated file.
            std::ofstream outputFile("scores.json");
            outputFile << jsonHighScore.dump(4);
            outputFile.close();
        }
        catch (json::parse_error &e)
        {
            std::cout << "Error parsing JSON." << std::endl;
        }
    }
}

bool highScores::compareHighScore()
{
    bool isScoreReplace = false;
    size_t replacePosition = -1;
    int lowestScore = std::numeric_limits<int>::max();

    // Open scores file.
    std::ifstream inputFile("scores.json");

    if (!inputFile.is_open())
    {
        std::cout << "Failed to load scores.json" << std::endl;
    }
    else
    {
        try
        {
            // Parse the JSON.
            json jsonHighScore = json::parse(inputFile);

            // Iterate over all scores in the JSON file.
            for (size_t i = 0; i < jsonHighScore.size(); i++)
            {
                int score = jsonHighScore[i]["score"];

                // Check if this score is lower than the current score.
                if (score < gameMain.getScore() && score < lowestScore)
                {
                    lowestScore = score;
                    replacePosition = i;
                }
            }

            if (replacePosition != -1)
            {
                isScoreReplace = true;
            }
        }
        catch (json::parse_error &e)
        {
            std::cout << "Error parsing JSON." << std::endl;
        }
    }
    return isScoreReplace;
}

void highScores::createNewHighScores()
{
    json jsonData = json::array();

    // Build 10 empty entries.
    for (int i = 0; i < 10; i++)
    {
        jsonData.push_back({{"name", ""}, {"score", 0}});
    }

    std::ofstream scoresFile("scores.json");
    if (scoresFile.is_open())
    {
        scoresFile << jsonData.dump(4);
        scoresFile.close();
    }
    else
    {
        std::cout << "Error creating highscores file.";
    }
}

std::string highScores::getHighScores()
{
    // Highscore string to append scores from file.
    std::string highScores;

    // Open scores file.
    std::ifstream inputFile("scores.json");

    if (!inputFile.is_open())
    {
        highScores = "Error loading scores.";
        std::cout << "Failed to load scores.json" << std::endl;
    }
    else
    {
        try
        {
            // Parse the JSON.
            json jsonHighScore = json::parse(inputFile);

            // Iterate through json.
            for (const auto &entry : jsonHighScore)
            {
                highScores += entry["name"].get<std::string>() + " " + std::to_string(entry["score"].get<int>()) + "\n";
            }
        }
        catch (json::parse_error &e)
        {
            highScores = "Error loading scores. \n";
            std::cout << "Error parsing JSON: " << e.what() << std::endl;
        }
    }

    // Return built string.
    return highScores;
}
