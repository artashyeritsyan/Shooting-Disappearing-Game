#include "game.hpp"

namespace {

const int SCORE_AMOUNT = 100; 

//time in milliseconds
const int GAME_SPEED = 4500;
const int SPEED_COEFFICIENT = 300;

std::chrono::milliseconds rowGenerationTime{GAME_SPEED};
const std::chrono::milliseconds BULLET_MUVING_TIME{25};
const std::chrono::milliseconds SHOT_COOLDOWN_TIME{160};
const std::chrono::milliseconds GAME_SPEED_UP_TIME{30000};

TimePoint rowGenerationStartTime;
TimePoint bulletMovingStartTime;
TimePoint shotCooldownStartTime;
TimePoint speedUpStartTime;

} // unnamed namespace

Game::Game() {
    Board board;
    GameScreen screen;
    ScoreManager scoreManager;

    lossStatus = false;

    rowGenerationStartTime = std::chrono::steady_clock::now();
    bulletMovingStartTime = std::chrono::steady_clock::now();
    shotCooldownStartTime = std::chrono::steady_clock::now();
    speedUpStartTime = std::chrono::steady_clock::now();

    cursorX = BOARD_WIDTH / 2;
    cursorY = BOARD_HEIGHT - 1;
}

void Game::start() {
    Input input;

    while (!lossStatus) {
        inputActions(input.inputHandling());
        cooldownManager();

        board.updatePlayerPosition(cursorX, cursorY);
        
        screen.updateGameWindow(board.getTable());
        screen.updateScoreDisplay(scoreManager.getScore(), scoreManager.getHighScore(), scoreManager.getSpeed());
    }
}

void Game::inputActions(EControls action) { 
    switch (action)
    {
    case left:
        if (cursorX > 0)
           --cursorX;
        break;
    case right:
        if (cursorX < BOARD_WIDTH - 1)
            ++cursorX;
        break;
    case up:
            shootManager();
        break;
    case quit:
        lossStatus = true;
        break;
    }
}

void Game::cooldownManager() {
    auto currentTime = std::chrono::steady_clock::now();
    
    if (currentTime - rowGenerationStartTime >= rowGenerationTime) {
        if(!board.checkLossStatus()) {
            board.addNewLine();
        }
        else {
            lossStatus = true;
        }
        rowGenerationStartTime = currentTime;
    }

    if (currentTime - bulletMovingStartTime >= BULLET_MUVING_TIME) {
        board.moveBulletsUp();

        if (board.checkToDestroyLine()) {
            scoreManager.increaseScore(SCORE_AMOUNT);
        }
        bulletMovingStartTime = currentTime;
    }

    if (currentTime - speedUpStartTime >= GAME_SPEED_UP_TIME) {
        scoreManager.increaseSpeed();
        speedUpStartTime = currentTime;

        rowGenerationTime = std::chrono::milliseconds{GAME_SPEED - (scoreManager.getSpeed() * SPEED_COEFFICIENT)};
    }
}

void Game::shootManager() {
    auto currentTime = std::chrono::steady_clock::now();

    if (currentTime - shotCooldownStartTime >= SHOT_COOLDOWN_TIME) {
        shotCooldownStartTime = currentTime;

        board.shoot(cursorX);
    }
}