#include "game.hpp"

Game::Game() {
    Board board;
    GameScreen screen;
    ScoreManager scoreManager;

    std::chrono::milliseconds rowGenerationTime(gameSpeed - (scoreManager.getSpeed() * speedCoefficient));

    rowGenerationStartTime = std::chrono::steady_clock::now();
    bulletMovingStartTime = std::chrono::steady_clock::now();
    shotCooldownStartTime = std::chrono::steady_clock::now();
    speedUpStartTime = std::chrono::steady_clock::now();

    cursorX = boardWidth / 2;
    cursorY = boardHeight - 1;
}

Game::~Game() {

}

void Game::start() {
    while (!board.getIsLose()) {
        inputHandling();
        cooldownManager();

        board.updatePlayerPosition(cursorX, cursorY);
        
        screen.updateGameWindow(board.getTable());
        screen.updateScoreDisplay(scoreManager.getScore(), scoreManager.getHighScore(), scoreManager.getSpeed());
    }
}

void Game::inputHandling() {
    char inputKey;
    inputKey = getch();

    switch (inputKey)
    {
    case 'a':  //TODO: implement this input with KEY_LEFT, and etc.
        if (cursorX > 0)
           --cursorX;
        break;
    case 'd':
        if (cursorX < boardWidth - 1)
            ++cursorX;
        break;
    case 'w':
    case ' ':
            shootManager();
        break;
    case 'q':
    case 'Q':
        //TODO: create logic to end game
        break;
    }
}

void Game::cooldownManager() {
    auto currentTime = std::chrono::steady_clock::now();
    
    if (currentTime - rowGenerationStartTime >= rowGenerationTime) {
        board.addNewLine();
        rowGenerationStartTime = currentTime;
    }

    if (currentTime - bulletMovingStartTime >= bulletMovingTime) {
        board.moveBulletsUp();
        if (board.checkToDestroyLine()) {
            scoreManager.increaseScore(scoreAmount);
        }
        bulletMovingStartTime = currentTime;
    }

    if (currentTime - speedUpStartTime >= speedUpTime) {
        scoreManager.increaseSpeed();
        speedUpStartTime = currentTime;

        rowGenerationTime = std::chrono::milliseconds{gameSpeed - (scoreManager.getSpeed() * speedCoefficient)};
    }
}

void Game::shootManager() {
    auto currentTime = std::chrono::steady_clock::now();

    if (currentTime - shotCooldownStartTime >= shotCooldownTime) {
        shotCooldownStartTime = currentTime;

        board.shoot(cursorX);
    }
}