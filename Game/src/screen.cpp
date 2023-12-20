#include "screen.hpp"

namespace {

const int GAME_SCREEN_HEIGHT = 20;
const int GAME_SCREEN_WIDTH = 20;
const int SCORE_SCREEN_HEIGHT = 20;
const int SCORE_SCREEN_WIDTH = 10;
const int OFFSET_X = 1;
const int OFFSET_Y = 1;

const std::string screenTexts[3] = {
    "SCORE",
    "HI-SCORE",
    "SPEED"
};

const std::string buttons[4] = {
    "Play",
    "Settings",
    "Help",
    "Exit",
};

inline std::pair<int, int> getScreenMaxDims() {
    int max_x;
    int max_y;
    getmaxyx(stdscr, max_y, max_x);
    return {max_x, max_y};
}

void initScreen() {
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    start_color();

    init_pair(1, COLOR_BLACK, COLOR_CYAN);
    init_pair(2, COLOR_CYAN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
}

WINDOW *initializeWindow(int screenSize_y, int screenSize_x,
                         int screenPos_y,  int screenPos_x) {

    return newwin(screenSize_y, screenSize_x, screenPos_y, screenPos_x);
}

} // unnamed namepace

GameScreen::GameScreen() {
    initScreen();
    createGameWindow();
}

void GameScreen::createGameWindow() {
    const auto [gameScreenX, gameScreenY] = computeScreenDims();

    gameWindow = initializeWindow(GAME_SCREEN_HEIGHT + 2,
                                  GAME_SCREEN_WIDTH + 2,
                                  gameScreenY,
                                  gameScreenX);

    scoreWindow = initializeWindow(SCORE_SCREEN_HEIGHT + 2,
                                   SCORE_SCREEN_WIDTH + 2,
                                   gameScreenY,
                                   gameScreenX + GAME_SCREEN_WIDTH + 2);
}

std::pair<int, int> GameScreen::computeScreenDims() const {
    const auto [max_x, max_y] = getScreenMaxDims();
    const int screenY = max_y/2 - (GAME_SCREEN_HEIGHT + 2)/2;
    const int screenX = max_x/2 - (GAME_SCREEN_WIDTH + SCORE_SCREEN_WIDTH + 4)/2;
    return {screenX, screenY};
}



GameScreen::~GameScreen() {
    delwin(gameWindow);
    delwin(scoreWindow);
    endwin();
} 

void GameScreen::updateGameWindow(matrixOfCube table) {
    werase(gameWindow);
    box(gameWindow, 0, 0);

    int colorNumber = 2;

    for (int row = 0; row < GAME_SCREEN_HEIGHT; ++row) 
    {
        for (int col = 0; col < GAME_SCREEN_WIDTH; col += 2) 
        {
            colorNumber = 2;
            if (table[row][col / 2].getBlock()) {
                colorNumber = 1;
            }
            wattron(gameWindow, COLOR_PAIR(colorNumber));
            mvwprintw(gameWindow, OFFSET_Y + row, OFFSET_X + col, "  ");
            wattroff(gameWindow, COLOR_PAIR(colorNumber));
        }
    }

    wrefresh(gameWindow);
}

void GameScreen::updateScoreDisplay(int score, int highScore, int speed) {
    werase(scoreWindow);
    box(scoreWindow, 0, 0);

    int parametersCount = 3;
    int offset = 3;

    printScoreDisplay(2, 0, score);
    printScoreDisplay(5, 1, highScore);
    printScoreDisplay(8, 2, speed);
    
    wrefresh(scoreWindow);
}

void GameScreen::printScoreDisplay(int offsetY, int textIndex, int value) {
    int valueLength = std::to_string(value).length();
    mvwprintw(scoreWindow, offsetY, (SCORE_SCREEN_WIDTH - screenTexts[textIndex].length()) / 2 + 1, screenTexts[textIndex].c_str());
    mvwprintw(scoreWindow, offsetY + 1, (SCORE_SCREEN_WIDTH - valueLength) / 2 + 1, "%d", value);
}

MenuScreen::MenuScreen() {
    initScreen();

    int max_x;
    int max_y;
    getmaxyx(stdscr, max_y, max_x);

    menuWindow = initializeWindow(menuScreenHeight + 2,
                                 menuScreenWidth + 2,
                                 max_y/2 - (menuScreenHeight + 2)/2,
                                 max_x/2 - (menuScreenWidth + 2)/2);    
}

MenuScreen::~MenuScreen()
{
    delwin(menuWindow);
    endwin();
}

void MenuScreen::updateMenuWindow(int choice) {
    werase(menuWindow);
    box(menuWindow, 0, 0);

    int OFFSET_X;
    int OFFSET_Y = menuScreenHeight / buttons->length();
    for (int i = 0; i < buttons->length(); i++) {
            wattron(menuWindow, COLOR_PAIR(3));

        if (i == choice) {
            wattron(menuWindow, A_REVERSE);
        }

        OFFSET_X = (menuScreenWidth - buttons[i].length()) / 2 + 1;
        mvwprintw(menuWindow, OFFSET_Y * (i+1), OFFSET_X, buttons[i].c_str());

        wattroff(menuWindow, A_REVERSE);
        wattroff(menuWindow, COLOR_PAIR(3));
    }

    wrefresh(menuWindow);
}

void MenuScreen::showHelpWindow() {
    werase(menuWindow);
    box(menuWindow, 0, 0);

    mvwprintw(menuWindow, 4, 2, "Controls");
    mvwprintw(menuWindow, 6, 2, "right = ->");
    mvwprintw(menuWindow, 8, 0, "right = <-");
    mvwprintw(menuWindow, 10, 0, "shoot = 'space'");
    werase(menuWindow);

    nodelay(stdscr, FALSE);
    int a = getch();
    nodelay(stdscr, TRUE);
}
