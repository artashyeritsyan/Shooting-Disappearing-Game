#pragma once

#include <iostream>
#include <fstream>

class ScoreManager {
private:
    static int highScore;
    int score;

    void updateHighScore();

public:
    ScoreManager();
    ~ScoreManager();
    void loadScoreFromFile();
    void saveScoreInFile();
    int getHighScore();
    void increaseScore(int score);
    int getScore();
};