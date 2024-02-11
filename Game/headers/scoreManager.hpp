#ifndef SCORE_MANAGER_HPP
#define SCORE_MANAGER_HPP

#include <iostream>
#include <fstream>

class ScoreManager {
public:
    ScoreManager();
    ~ScoreManager();

    void loadScoreFromFile();
    void saveScoreInFile();
    int getHighScore();
    int getScore();
    void increaseScore(int score);
    int getSpeed();
    void increaseSpeed();

private:
    void updateHighScore();

    int highScore;
    int score;
    int speed;
};

#endif // SCORE_MANAGER_HPP