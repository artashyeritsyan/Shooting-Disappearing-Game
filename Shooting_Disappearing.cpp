#include <array>
#include <iostream>
#include <curses.h>
#include <chrono>
#include <thread>

struct pixel{
    int x;
    int y;
    char symbol;
    bool isShoot;
};

const int g_height = 20;
const int g_width = 10;
const char g_pixelSymbol = '#';
const char g_emptySpaceSymbol = '^';

int cursorX = g_width / 2;
int cursorY = g_height - 1;
std::array<std::array<char, g_width>, g_height> g_table;
std::array<std::array<bool, g_width>, g_height> g_movingMatrix;

void mainMenu();
void play(WINDOW* win);
void moveSymbols(std::array<bool, g_height>& destructingRows);
void shoot();
void screenRefresh(WINDOW* win);
bool rowDestructionCheck(int rowIndex);
bool rowDestruction(std::array<bool, g_height> &destructingRows);

int main() {
    mainMenu(); 
    return 0;
}

void mainMenu()
{
    initscr();
    keypad(stdscr, TRUE);
    WINDOW* win = newwin(g_height, g_width, 0, 0);
    wrefresh(win);

    curs_set(0);
    play(win);
    curs_set(1);

    endwin();
}

void play(WINDOW* win) {
    std::array<bool, g_height> destructingRows {false};
    std::string cursor = " # \n###";
    int inputKey;

    noecho();
    wrefresh(win);
    nodelay(stdscr, TRUE);
    curs_set(0);

    for (int i = 0; i < g_height; i++) {
            for (int j = 0; j < g_width; j++) {
                g_table[i][j] = g_emptySpaceSymbol;
            }
        }
        
    while(true)
    {
        inputKey = 0;

        if(rowDestruction(destructingRows))
            screenRefresh(win);

        for (int i = 18; i < g_height; i++) {
            for (int j = 0; j < g_width; j++) {
                g_table[i][j] = g_emptySpaceSymbol;
            }
        }

        
        // TODO: Es masi logiakan tanel zangvaci (table)-i mej

        mvaddch(cursorY, cursorX, g_pixelSymbol);
        g_table[cursorY][cursorX] = g_pixelSymbol;
        g_table[cursorY - 1][cursorX] = g_pixelSymbol;
        if(cursorX != g_width - 1)
            g_table[cursorY][cursorX + 1] = g_pixelSymbol;
        if(cursorX != 0)
            g_table[cursorY][cursorX - 1] = g_pixelSymbol;
        
        moveSymbols(destructingRows);
        //usleep(10000); 

        screenRefresh(win);   
    //TODO: Nenc anel vor chspasi im inputin
        inputKey = getch();
        switch (inputKey) {
            case KEY_LEFT:
                if (cursorX > 0) cursorX--;
                break;
            case KEY_RIGHT:
                if (cursorX < g_width - 1) cursorX++;
                break;
            case KEY_UP:
                shoot();
                break;
            case 'q':
            case 'Q':
                endwin();
        }   
    }
}

void moveSymbols(std::array<bool, g_height>& destructingRows)
{
    for(int i = 0; i < g_height; ++i) {
        for(int j = 0; j < g_width; ++j) {
            if(g_movingMatrix[i][j]) {                
                if(i - 1 >= 0 && (g_table[i - 1][j] != g_pixelSymbol)) {
                    g_table[i - 1][j] = g_pixelSymbol;
                    g_table[i][j] = g_emptySpaceSymbol;

                    g_movingMatrix[i][j] = false;

                    if(i - 2 >= 0 && (g_table[i - 2][j] != g_pixelSymbol)) {
                        g_movingMatrix[i - 1][j] = true;

                    }
                }
                else {
                    g_movingMatrix[i][j] = false;
                }
                if(rowDestructionCheck(i - 1))
                    destructingRows[i - 1] = true;                     
            }
        }
    }
}

void shoot() {
    int bulletIndexY = g_height - 3;
    const int bulletIndexX = cursorX;

    g_movingMatrix[bulletIndexY][bulletIndexX] = true;
    g_table[bulletIndexY][bulletIndexX] = g_pixelSymbol;
}

void screenRefresh(WINDOW* win) {
    werase(win);

    for (int i = 0; i < g_height; i++) {
            for (int j = 0; j < g_width; j++) {
                waddch(win, g_table[i][j]);
            }
        }

    wrefresh(win);
}

bool rowDestructionCheck(int row) {
    for (int i = 0; i < g_width; ++i) {
        if (g_table[row][i] != g_pixelSymbol && !g_movingMatrix[row][i]) {
            return false;
        }
    }
    return true;
}

bool rowDestruction(std::array<bool, g_height> &destructingRows) {
    std::array<std::array<char, g_width>, g_height> tempTable = g_table;
    //bool needToRefresh;
    int endRow = g_height - 3;

    for(int rowIndex = 0; rowIndex < g_height - 2; ++rowIndex) {
        if(destructingRows[rowIndex]) {
            int j = rowIndex;
            while (j < endRow) {
                for (int i = 0; i < g_width; ++i) {
                    g_table[j][i] = tempTable[j + 1][i];
                }
                ++j;
            }
            destructingRows[rowIndex] = false;
            //needToRefresh = true;
            return true;
        }
    }
    return false;
    
}