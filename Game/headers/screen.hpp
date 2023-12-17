#ifndef GAME_SCREEN_HPP
#define GAME_SCREEN_HPP

#include <iostream>
#include <ncurses.h>

#include "board.hpp"

class GameScreen {
public:
    GameScreen();
    ~GameScreen();

    void updateGameWindow(matrixOfCube table);
    void updateScoreDisplay(int score, int hightScore, int speed);

private:
    // void initScreen();
    void createWindows();
    std::pair<int, int> computeScreenDims() const;

private:
    WINDOW *gameWindow;
    WINDOW *scoreWindow;
};


class MenuScreen {
public:
    MenuScreen();
    ~MenuScreen();
    void updateMenuWindow(int choice);

private:
    const int menuScreenHeight = 9;
    const int menuScreenWidth = 14;

    WINDOW *menuWindow;
};

class RestartScreen { 

public:
    RestartScreen();
    ~RestartScreen();
    void updateRestartScreen();

private:
    const int restartScreenHeight = 10;
    const int restartScreenWidth = 10;

    WINDOW *restartWindow;
};

#endif // GAME_SCREEN_HPP