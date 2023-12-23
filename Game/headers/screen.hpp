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
    void createGameWindow();
    std::pair<int, int> computeScreenDims() const;
    void printScoreDisplay(int offsetY, int textIndex, int value);

private:
    WINDOW *gameWindow;
    WINDOW *scoreWindow;
};


class MenuScreen {
public:
    MenuScreen();
    ~MenuScreen();
    void updateMenuWindow(int choice);
    void showHelpWindow();

private:
    const int menuScreenHeight = 9;
    const int menuScreenWidth = 14;

    WINDOW *menuWindow;
};

#endif // GAME_SCREEN_HPP
