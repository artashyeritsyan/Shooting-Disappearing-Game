#include "screen.hpp"

Screen::Screen() {
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    start_color();

    init_pair(1, COLOR_BLACK, COLOR_CYAN);
    init_pair(2, COLOR_RED, COLOR_BLACK);

    highScore = 0;
    loadScoreFromFile();
}
int Screen::highScore = 0;

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

GameScreen::GameScreen():Screen() {
    score = 0;

    int max_x;
    int max_y;

    getmaxyx(stdscr, max_y, max_x);

    const int gameScreenY = max_y/2 - (gameScreenHeight + 2)/2;
    const int gameScreenX = max_x/2 - (gameScreenWidth + scoreScreenWidth + 4)/2;

    // if(max_x <= gameScreenWidth + scoreScreenWidth || max_y <= gameScreenHeight + scoreScreenHeight) {
    //     std::cout << "screen too small for display game" << std::endl;
    //     exit(0);
    // }

    gameWindow = newwin(gameScreenHeight + 2,
                        gameScreenWidth + 2,
                        gameScreenY,
                        gameScreenX);

    scoreWindow = newwin(scoreScreenHeight + 2,
                         scoreScreenWidth + 2,
                         gameScreenY,
                         gameScreenX + gameScreenWidth + 2);
    
    box(gameWindow, 0, 0);
    box(scoreWindow, 0, 0);

    refresh();
}

GameScreen::~GameScreen() {
    delwin(gameWindow);
    delwin(scoreWindow);
    endwin();
}

void GameScreen::updateGameWindow(matrixOfCube table) {
    werase(gameWindow);
    box(gameWindow, 0, 0);

    for (int row = 0; row < gameScreenHeight; ++row) 
    {
        for (int col = 0; col < gameScreenWidth; col += 2) 
        {
            //TODO: fix this line "col / 2" part, create another logic
            if (table[row][col / 2].getBlock()) {
                wattron(gameWindow, COLOR_PAIR(1));
                mvwaddch(gameWindow, offsetY + row, offsetX + col, ' ');
                mvwaddch(gameWindow, offsetY + row, offsetX + col + 1, ' ');
                wattroff(gameWindow, COLOR_PAIR(1));
            }
            else {
                wattron(gameWindow, COLOR_PAIR(2));
                mvwaddch(gameWindow, offsetY + row, offsetX + col, ' ');
                mvwaddch(gameWindow, offsetY + row, offsetX + col + 1, ' ');
                wattroff(gameWindow, COLOR_PAIR(2));
            }
        }
    }

    wrefresh(gameWindow);
}

void GameScreen::increaseScore() {
    score += 100;
    updateHighScore(score);
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

