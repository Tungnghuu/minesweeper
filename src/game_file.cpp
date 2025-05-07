#include "game.h"
#include <fstream>

void SaveHighScores(){
    std::ofstream file("data/highscores.txt");
    if (file.is_open()) {
        file << highScoreEasy << '\n';
        file << highScoreMedium << '\n';
        file << highScoreHard << '\n';
        file.close();
    }
}

void LoadHighScores(){
    std::ifstream file("data/highscores.txt");
    if (file.is_open()) {
        file >> highScoreEasy;
        file >> highScoreMedium;
        file >> highScoreHard;
        file.close();
    }
}