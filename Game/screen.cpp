#include "screen.hpp"

Screen::Screen() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
}

Screen::~Screen() {

}

void Screen::updateHighScore(int score) {
    if(score > highScore)
        highScore = score;
}

int Screen::getHighScore() {
    return highScore;
}

void Screen::saveScoreInFile() {
    //TODO: Implement logic to save score in file
}

void Screen::loadScoreFromFile() {
    //TODO: Implement logic to load score from file
}



GameScreen::GameScreen() {
    score = 0;

    int max_x;
    int max_y;
    getmaxyx(stdscr, max_x, max_y);

    const int gameScreenY = max_y/2 - (gameScreenHeight + 2)/2;
    const int gameScreenX = max_x/2 - (gameScreenwidth + scoreScreenWidth + 4)/2;

    if(max_x <= gameScreenwidth + scoreScreenWidth || max_y <= gameScreenHeight + scoreScreenHeight) {
        std::cout << "screen too small for display game" << std::endl;
        exit(0);
    }

    gameWindow = newwin(gameScreenHeight + 2,
                        gameScreenwidth + 2,
                        gameScreenY,
                        gameScreenX); 

    scoreWindow = newwin(scoreScreenHeight + 2,
                         scoreScreenWidth + 2,
                         gameScreenY,
                         gameScreenX + gameScreenwidth + 2);
    
    box(gameWindow, 0, 0);
    box(scoreWindow, 0, 0);

    refresh();
}

GameScreen::~GameScreen() {
    delwin(gameWindow);
    delwin(scoreWindow);
    endwin();
}

void GameScreen::updateGameWindow() {
    wrefresh(gameWindow);
}

void GameScreen::updateScore(int amount) {
    score += amount;
    updateHighScore(score);
    updateScoreDisplay();
}

void GameScreen::updateScoreDisplay() {
    werase(scoreWindow);
    box(scoreWindow, 0, 0);

    mvwprintw(scoreWindow, 1, 1, "  SCORE");
    mvwprintw(scoreWindow, 2, 1, "    %d", score);

    mvwprintw(scoreWindow, 3, 1, " HI-SCORE");
    mvwprintw(scoreWindow, 4, 1, "    %d", getHighScore());

    wrefresh(scoreWindow);
}



MenuScreen::MenuScreen() {
    int max_x;
    int max_y;
    getmaxyx(stdscr, max_x, max_y);

    if(max_x <= menuScreenWidth || max_y <= menuScreenHeight) {
    std::cout << "screen too small for display game" << std::endl;
    exit(0);
    }

    menuWindow = newwin(menuScreenHeight + 2,
                        menuScreenWidth + 2,
                        max_y/2 - (menuScreenHeight + 2)/2,
                        max_x/2 - (menuScreenWidth + 2)/2);
    
    box(menuWindow, 0, 0);
}

MenuScreen::~MenuScreen()
{
    delwin(menuWindow);
    endwin();
}

void MenuScreen::updateMenuWindow() {
    wrefresh(menuWindow);
}

// int main() {
//     GameScreen screen;

//     // Example: Update the score by 50
//     GameScreen::updateScore(50);
//     screen.updateGameWindow();
//     getch(); // Wait for a key press

//     // Example: Update the score by 100 and save it to HighScore
//     GameScreen::updateScore(100);
//     screen.updateGameWindow();
//     getch(); // Wait for a key press

//     return 0;
// }

