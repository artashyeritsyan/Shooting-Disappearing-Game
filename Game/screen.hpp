#include <iostream>
#include <ncurses.h>
#include <fstream>

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
    const int gameScreenwidth = 20;
    const int scoreScreenHeight = 20;
    const int scoreScreenWidth = 10;

    int score;

    WINDOW *gameWindow;
    WINDOW *scoreWindow;

public:
    GameScreen();
    ~GameScreen();

    void updateGameWindow();
    void updateScore(int amount);
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