#include "scoreManager.hpp"

ScoreManager::ScoreManager(){
    score = 0;
    loadScoreFromFile();
}

ScoreManager::~ScoreManager(){
    score = 0;
    saveScoreInFile();
}

int ScoreManager::highScore = 0;

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

void ScoreManager::saveScoreInFile() {
    //TODO: Implement logic to save score in file
}

void ScoreManager::loadScoreFromFile() {
    //TODO: Implement logic to load score from file
}

void ScoreManager::updateHighScore() {
    if(score > highScore) {
        highScore = score;
    }
}
