#include "game.hpp"

Game::Game() {
    GameScreen screen;
    Board board;

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
        
    //    std::cout << cursorX << std::endl;
        inputHandling();
        cooldownManager();

        board.updatePlayerPosition(cursorX, cursorY);
        
        screen.updateGameWindow(board.getTable());
        screen.updateScoreDisplay();
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
        bulletMovingStartTime = currentTime;
    }

    //std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

void Game::shootManager() {
    auto currentTime = std::chrono::steady_clock::now();

    if (currentTime - shotCooldownStartTime >= shotCooldownTime) {
        bulletMovingStartTime = currentTime;

        board.shoot(cursorX);
    }
}