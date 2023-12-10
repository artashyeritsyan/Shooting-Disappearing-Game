#pragma once

#include <iostream>
#include <ncurses.h>

#include "board.hpp"

class Screen
{
private:
public:
    Screen();
    ~Screen();
};


class GameScreen:Screen {
private : 
    const int gameScreenHeight = 20;
    const int gameScreenWidth = 20;
    const int scoreScreenHeight = 20;
    const int scoreScreenWidth = 10;

    int offsetX = 1;
    int offsetY = 1;

    WINDOW *gameWindow;
    WINDOW *scoreWindow;

public:
    GameScreen();
    ~GameScreen();

    void updateGameWindow(matrixOfCube table);
    void updateScoreDisplay(int score, int hightScore);
};


class MenuScreen:Screen {
private:
    const int menuScreenHeight = 9;
    const int menuScreenWidth = 14;

    WINDOW *menuWindow;

    const std::string buttons[4] = {
    "Play",
    "Settings",
    "Help",
    "Exit",
    };

public:
    MenuScreen();
    ~MenuScreen();
    void updateMenuWindow(int choice);
};

class RestartScreen:Screen { 
    const int restartScreenHeight = 10;
    const int restartScreenWidth = 10;

    WINDOW *restartWindow;

public:
    RestartScreen();
    ~RestartScreen();
    void updateRestartScreen();
};