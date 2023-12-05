#include "game.hpp"

Game::Game() {
    rowGenerationStartTime = std::chrono::steady_clock::now();
    bulletMovingStartTime = std::chrono::steady_clock::now();
    shotCooldownStartTime = std::chrono::steady_clock::now();

    cursorX = boardWidth / 2;
    cursorY = boardHeight - 1;
}

Game::~Game() {

}

void Game::start() {
    /*TODO: Create Timer-, While loop-, Input-,
     Calling functions(AddNewLine-, Shoot-, RefreshScreen-) -

     And create function and logic for loose !!
    */

    while (true) {
        inputHandling();
        cooldownManager();
        board.updatePlayerPosition(cursorX, cursorY);
        
        screen.updateGameWindow(board.getTable());
    }

}

void Game::inputHandling() {
    char inputKey = getch();

    switch (inputKey)
    {
    case KEY_LEFT:
        if (cursorX > 0)
           --cursorX;
        break;
    case KEY_RIGHT:
        if (cursorX < boardWidth - 1)
            ++cursorX;
        break;
    case KEY_UP:        
            shootManager();
        break;
    case 'q':
    case 'Q':
        //TODO: create logic to end game
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

        bulletMovingStartTime = currentTime;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

void Game::shootManager() {
    auto currentTime = std::chrono::steady_clock::now();

    if (currentTime - shotCooldownStartTime >= shotCooldownTime) {
        board.shoot(cursorX);

        bulletMovingStartTime = currentTime;
    }
}