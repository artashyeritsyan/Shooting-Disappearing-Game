#include "scoreManager.hpp"

ScoreManager::ScoreManager(){
    score = 0;
    speed = 1;
    loadScoreFromFile();
}

ScoreManager::~ScoreManager(){
    score = 0;
    saveScoreInFile();
}

int ScoreManager::getHighScore() {
    return highScore;
}

int ScoreManager::getScore() {
    return score;
}

void ScoreManager::increaseScore(int score) {
    this->score += score;
    updateHighScore();
}

int ScoreManager::getSpeed() {
    return speed;
}

void ScoreManager::increaseSpeed() {
    ++speed;
}

void ScoreManager::saveScoreInFile() {
    std::ofstream file("data/high_score.txt", std::ios::out);

    if (file.is_open()) {
        file << highScore << std::endl;
        file.close();
    }
}

void ScoreManager::loadScoreFromFile() {
    std::ifstream file("data/high_score.txt");
    int value = 0;

    if (file.is_open()) {
        file >> value;
        file.close();
    }

    if(value){
        highScore = value;
    }
}

void ScoreManager::updateHighScore() {
    if(score > highScore) {
        highScore = score;
        saveScoreInFile();
    }
}

