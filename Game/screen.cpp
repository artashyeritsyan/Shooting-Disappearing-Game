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


} // unnamed namepace


GameScreen::GameScreen() {
    static const auto initialized = initScreen();
    createWindows();
}

void GameScreen::createWindows() {
    const auto [gameScreenX, gameScreenY] = computeScreenDims();
    gameWindow = newwin(GAME_SCREEN_HEIGHT + 2,
                        GAME_SCREEN_WIDTH + 2,
                        gameScreenY,
                        gameScreenX);
    scoreWindow = newwin(SCORE_SCREEN_HEIGHT + 2,
                         SCORE_SCREEN_WIDTH + 2,
                         gameScreenY,
                         gameScreenX + GAME_SCREEN_WIDTH + 2);
    box(scoreWindow, 0, 0);
    refresh();
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

    for (int row = 0; row < GAME_SCREEN_HEIGHT; ++row) 
    {
        for (int col = 0; col < GAME_SCREEN_WIDTH; col += 2) 
        {
            //TODO: fix this line "col / 2" part, create another logic
            if (table[row][col / 2].getBlock()) {
                wattron(gameWindow, COLOR_PAIR(1));
                mvwaddch(gameWindow, OFFSET_Y + row, OFFSET_X + col, ' ');
                mvwaddch(gameWindow, OFFSET_Y + row, OFFSET_X + col + 1, ' ');
                wattroff(gameWindow, COLOR_PAIR(1));
            }
            else {
                wattron(gameWindow, COLOR_PAIR(2));
                mvwaddch(gameWindow, OFFSET_Y + row, OFFSET_X + col, ' ');
                mvwaddch(gameWindow, OFFSET_Y + row, OFFSET_X + col + 1, ' ');
                wattroff(gameWindow, COLOR_PAIR(2));
            }
        }
    }

    wrefresh(gameWindow);
}

void GameScreen::updateScoreDisplay(int score, int highScore, int speed) {
    werase(scoreWindow);
    box(scoreWindow, 0, 0);

    int scoreLength = std::to_string(score).length();
    int highScoreLength = std::to_string(highScore).length();
    int speedLength = std::to_string(speed).length();
    
    mvwprintw(scoreWindow, 2, (SCORE_SCREEN_WIDTH - screenTexts[0].length()) / 2 + 1, screenTexts[0].c_str());
    mvwprintw(scoreWindow, 3, (SCORE_SCREEN_WIDTH - scoreLength) / 2 + 1, "%d", score);

    mvwprintw(scoreWindow, 5, (SCORE_SCREEN_WIDTH - screenTexts[1].length()) / 2 + 1, screenTexts[1].c_str());
    mvwprintw(scoreWindow, 6, (SCORE_SCREEN_WIDTH - highScoreLength) / 2 + 1, "%d", highScore);

    mvwprintw(scoreWindow, 8, (SCORE_SCREEN_WIDTH - screenTexts[2].length()) / 2 + 1, screenTexts[2].c_str());
    mvwprintw(scoreWindow, 9, (SCORE_SCREEN_WIDTH - speedLength) / 2 + 1, "%d", speed);

    wrefresh(scoreWindow);
}



MenuScreen::MenuScreen() {
    initScreen();

    int max_x;
    int max_y;
    getmaxyx(stdscr, max_y, max_x);

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
