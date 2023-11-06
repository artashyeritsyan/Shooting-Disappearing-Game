#include <array>
#include <curses.h>
#include <cstdlib>
#include <iostream>
#include <thread>

struct pixel
{
    int x;
    int y;
    char symbol;
    bool isShoot;
};

bool loose = false;
const int g_height = 16;
const int g_width = 10;
const char g_pixelSymbol = 'Ա';
const char g_cursorSymbol = 'Ֆ';
const char g_emptySpaceSymbol = '.';

std::array<std::array<char, g_width>, g_height> g_table;
std::array<std::array<bool, g_width>, g_height> g_movingMatrix;

void mainMenu();
void play();
void moveSymbols(std::array<bool, g_height> &destructingRows);
void shoot(int cursorX);
void screenRefresh(WINDOW *win);
bool rowDestructionCheck(int rowIndex);
bool rowDestruction(std::array<bool, g_height> &destructingRows);
void shiftMovingMatrixUp(int startRow);
void shiftMovingMatrixDown();
void generateRow();
void looseCheck();
void menuButtons();
void chooseButtons(WINDOW *win, int cursorX);

int main()
{
    mainMenu();

    return 0;
}

void mainMenu()
{
    initscr();
    // start_color();
    keypad(stdscr, TRUE);
    curs_set(0);
    //WINDOW *win = newwin(g_height, g_width, 0, 0);
    //wrefresh(win);

    menuButtons();
    // play();
}

void play()
{
    WINDOW *win = newwin(g_height, g_width, 0, 0);

    int timer = 0;
    int coolDownTimer = 0;
    int ShootingCoolDown = 5000;
    int rowGenerationSpeed = 200000;
    int bulletFlightTime = 1500;
    
    int cursorX = g_width / 2;
    int cursorY = g_height - 1;

    std::array<bool, g_height> destructingRows{false};
    //std::string cursor = " # \n###";
    int inputKey;

    noecho();
    wrefresh(win);
    nodelay(stdscr, TRUE);
    curs_set(0);

    for (int i = 0; i < g_height; i++)
    {
        for (int j = 0; j < g_width; j++)
        {
            g_table[i][j] = g_emptySpaceSymbol;
        }
    }
    generateRow();
    generateRow();   

    while (!loose)
    {
        inputKey = 0;

        if (timer > rowGenerationSpeed)
        {
            timer = 0;
            if(rowGenerationSpeed > 100000)
            rowGenerationSpeed -= 10000;

            generateRow();
        }

        if (rowDestruction(destructingRows))
            screenRefresh(win);

        for (int i = g_height - 2; i < g_height; i++)
        {
            for (int j = 0; j < g_width; j++)
            {
                g_table[i][j] = g_emptySpaceSymbol;
            }
        }

        // TODO: Es masi logikan tanel zangvaci (table)-i mej

        mvaddch(g_height, g_width, ' ');
        g_table[cursorY][cursorX] = g_cursorSymbol;
        g_table[cursorY - 1][cursorX] = g_cursorSymbol;
        if (cursorX != g_width - 1)
            g_table[cursorY][cursorX + 1] = g_cursorSymbol;
        if (cursorX != 0)
            g_table[cursorY][cursorX - 1] = g_cursorSymbol;

        if(timer % bulletFlightTime == 0)
            moveSymbols(destructingRows);

        screenRefresh(win);

        inputKey = getch();
        switch (inputKey)
        {
        case KEY_LEFT:
            if (cursorX > 0)
                cursorX--;
            break;
        case KEY_RIGHT:
            if (cursorX < g_width - 1)
                cursorX++;
            break;
        case KEY_UP:
            if(coolDownTimer > ShootingCoolDown) {
                coolDownTimer = 0;
                shoot(cursorX);
            }
            break;
        case 'q':
        case 'Q':
            endwin();
        }

        ++timer;
        ++coolDownTimer;
    }
    endwin();
    menuButtons();
}

void moveSymbols(std::array<bool, g_height> &destructingRows)
{
    for (int i = 0; i < g_height; ++i)
    {
        for (int j = 0; j < g_width; ++j)
        {
            if (g_movingMatrix[i][j])
            {
                if (i - 1 >= 0 && (g_table[i - 1][j] != g_pixelSymbol))
                {
                    g_table[i - 1][j] = g_pixelSymbol;
                    g_table[i][j] = g_emptySpaceSymbol;

                    g_movingMatrix[i][j] = false;

                    if (i - 2 >= 0 && (g_table[i - 2][j] != g_pixelSymbol))
                    {
                        g_movingMatrix[i - 1][j] = true;
                    }
                }
                else
                {
                    g_movingMatrix[i][j] = false;
                }

                if (rowDestructionCheck(i - 1) && !g_movingMatrix[i - 1][j])
                    destructingRows[i - 1] = true;
            }
        }
    }
}

void shoot(int cursorX)
{
    int bulletIndexY = g_height - 3;
    const int bulletIndexX = cursorX;

    g_movingMatrix[bulletIndexY][bulletIndexX] = true;
    g_table[bulletIndexY][bulletIndexX] = g_pixelSymbol;
}

void screenRefresh(WINDOW *win)
{
    werase(win);

    for (int i = 0; i < g_height; i++)
    {
        for (int j = 0; j < g_width; j++)
        {
            waddch(win, g_table[i][j]);
        }
    }

    wrefresh(win);
}

bool rowDestructionCheck(int row)
{
    for (int i = 0; i < g_width; ++i)
    {
        if (g_table[row][i] != g_pixelSymbol && !g_movingMatrix[row][i])
        {
            return false;
        }
    }
    return true;
}

bool rowDestruction(std::array<bool, g_height> &destructingRows)
{
    std::array<std::array<char, g_width>, g_height> tempTable = g_table;
    int endRow = g_height - 3;

    for (int rowIndex = 0; rowIndex < g_height - 2; ++rowIndex)
    {
        if (destructingRows[rowIndex])
        {
            destructingRows[rowIndex] = false;
            int j = rowIndex;

            while (j < endRow)
            {
                for (int i = 0; i < g_width; ++i)
                {
                    g_table[j][i] = tempTable[j + 1][i];
                }
                ++j;
            }

            for(int i = 0; i < g_width; ++i)
                g_table[endRow][i] = g_emptySpaceSymbol;

            shiftMovingMatrixUp(rowIndex);

            return true;
        }
    }

    return false;
}

void generateRow()
{
    std::array<std::array<char, g_width>, g_height> tempTable = g_table;
    std::array<char, g_width> randomFilledRow;
    for (int i = 0; i < g_width; i++)
        randomFilledRow[i] = g_emptySpaceSymbol;

    int minRange = g_width / 3;
    int maxRange = g_width / 3 * 2;
    int pixelsCount = (rand() % (maxRange - minRange + 1)) + minRange;
    
    int position;
    for (int i = 0; i < pixelsCount; ++i)
    {
        do
        {
            position = rand() % g_width;
        } while (randomFilledRow[position] == g_pixelSymbol);
        randomFilledRow[position] = g_pixelSymbol;
    }

    int j = g_height - 2;
    int endRow = 0;

    while (j > endRow)
    {
        for (int i = 0; i < g_width; ++i)
        {
            g_table[j][i] = tempTable[j - 1][i];
        }
        --j;
    }

    for (int i = 0; i < g_width; ++i)
    {
        g_table[0][i] = randomFilledRow[i];
    }

    shiftMovingMatrixDown();

    looseCheck();
}

void shiftMovingMatrixUp(int startRow)
{
    std::array<std::array<bool, g_width>, g_height> tempTable = g_movingMatrix;

    int endRow = g_height - 2;
    int j = startRow;

    while (j < endRow)
    {
        for (int i = 0; i < g_width; ++i)
        {
            g_movingMatrix[j][i] = tempTable[j + 1][i];
        }
        ++j;
    }
}

void shiftMovingMatrixDown()
{
    std::array<std::array<bool, g_width>, g_height> tempTable = g_movingMatrix;

    int j = g_height - 2;
    int endRow = 0;
    while (j > endRow)
    {
        for (int i = 0; i < g_width; ++i)
        {
            g_movingMatrix[j][i] = tempTable[j - 1][i];
        }
        --j;
    }
}

void looseCheck()
{
    for (int i = 0; i < g_width; ++i)
    {
        if(g_table[g_height - 2][i] == g_pixelSymbol && !g_movingMatrix[g_height - 2][i])
        {
            loose = true;

            for(int i = 0; i < g_height; ++i)
            {
            for(int j = 0; j < g_width; ++j)
            {
                g_table[i][j] = '@';
            }
            }
        }
    }
}

void menuButtons()
{
    WINDOW *win = newwin(g_height, g_width, 0, 0);
    keypad(stdscr, TRUE);
    init_pair(1, COLOR_BLACK, COLOR_GREEN);
    attron(COLOR_PAIR(1));
    
    int cursorX = 0;
    int cursorY = 4;

    std::array<std::string, g_height> screen;
    int inputKey;
    
    for(int i = 0; i < g_height; ++i)
    {
        screen[i] = "          ";
    }

    screen[4] = "   PLAY   ";
    screen[7] = "  OPTIONS ";
    screen[10] = "  CREDITS ";
    screen[13] = "   EXIT   ";
    
    while(true)
    {
        inputKey = 0;
        werase(win);

        for (int i = 0; i < g_width; ++i)
        {
            mvaddch(cursorY, i, screen[cursorY][i]);
        }
        mvaddch(cursorY, cursorX, '>');

        for (int i = 0; i < g_height; i++)
        {
            for (int j = 0; j < g_width; j++)
            {
                waddch(win, screen[i][j]);
            }
        }

        wrefresh(win);
        inputKey = getch();
        switch (inputKey)
        {
        case KEY_UP:
            if (cursorY > 4)
                cursorY -= 3;
            break;
        case KEY_DOWN:
            if (cursorY < 13)
                cursorY += 3;
            break;
        case KEY_RIGHT:
            attroff(COLOR_PAIR(1));
            endwin();
            chooseButtons(win, cursorY);
            return;
            break;
        }
    }
}
void chooseButtons(WINDOW *win, int cursorY)
{
    switch (cursorY)
    {
        case 4:
            play();
            break;
        case 7:
            break;
        case 10:
            break;
        case 13:
            break;
    }
    return;
}