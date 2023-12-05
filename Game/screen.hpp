#include <iostream>
#include <ncurses.h>
#include <fstream>

#include "board.hpp"

class Screen
{
private:
    static int highScore;

protected:
    void saveScoreInFile();
    void updateHighScore(int score);
    int getHighScore();

public:
    Screen();
    ~Screen();
    void loadScoreFromFile();
};


class GameScreen:Screen {
private : 
    const int gameScreenHeight = 20;
    const int gameScreenWidth = 20;
    const int scoreScreenHeight = 20;
    const int scoreScreenWidth = 10;

    int score;
    int offsetX = 1;
    int offsetY = 1;

    WINDOW *gameWindow;
    WINDOW *scoreWindow;

public:
    GameScreen();
    ~GameScreen();

    void updateGameWindow(matrixOfCube table);
    void updateScore(int amount = 100);
    void updateScoreDisplay();
};


class MenuScreen:Screen {
private:
    const int menuScreenHeight = 10;
    const int menuScreenWidth = 10;
    WINDOW *menuWindow;
public:
    MenuScreen();
    ~MenuScreen();
    void updateMenuWindow();
};