#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#include <clocale>  // Include for wide character support

const int gameScreenWidth = 10;  // Adjust as needed
const int gameScreenHeight = 5;  // Adjust as needed
const int offsetX = 5;  // Adjust as needed

// Assuming matrixOfCube is a typedef for a 2D boolean array
typedef bool matrixOfCube[gameScreenHeight][gameScreenWidth];

class GameScreen {
public:
    GameScreen(WINDOW *win) : gameWindow(win) {}

    void updateGameWindow(matrixOfCube table) {
        werase(gameWindow);

        // Set the foreground and background colors for color pair 1
        wattron(gameWindow, COLOR_PAIR(1));

        for (int line = 0; line < gameScreenHeight; ++line) {
            for (int col = 0; col < gameScreenWidth; ++col) {
                if (table[line][col]) {
                    // Display a square symbol (U+2588) with color pair 1
                    mvwaddch(gameWindow, line, offsetX + col, ' ' | COLOR_PAIR(1));
                } else {
                    // Display a space with color pair 1
                    mvwaddch(gameWindow, line, offsetX + col, ' ' | COLOR_PAIR(2));
                }
            }
        }

        wattroff(gameWindow, COLOR_PAIR(1));

        wrefresh(gameWindow);
    }

private:
    WINDOW *gameWindow;
};

int main() {
    initscr();

    // Enable wide characters
    setlocale(LC_ALL, "");

    // Check if colors are supported
    if (has_colors()) {
        start_color();

        // Initialize color pair 1 with red foreground and black background
        init_pair(1, COLOR_BLACK, COLOR_RED);
        init_pair(2, COLOR_RED, COLOR_BLACK);
    } else {
        printw("Colors are not supported!");
        refresh();
        getch();
        endwin();
        return 1;
    }

    // Create the game window
    WINDOW *gameWin = newwin(gameScreenHeight, gameScreenWidth, 0, 0);

    GameScreen gameScreen(gameWin);

    // Seed for random number generation
    srand(static_cast<unsigned>(time(nullptr)));

    // Enter the endless loop
    while (true) {
        // Initialize matrix with random true/false values
        matrixOfCube randomTable;
        for (int i = 0; i < gameScreenHeight; ++i) {
            for (int j = 0; j < gameScreenWidth; ++j) {
                randomTable[i][j] = rand() % 2 == 0;
            }
        }

        // Update the game window with the random table
        gameScreen.updateGameWindow(randomTable);

        // Refresh the screen
        refresh();

        // Wait for a key press (non-blocking)
        if (getch() == 'q') {
            break;  // Exit the loop if 'q' is pressed
        }
    }

    endwin();
    return 0;
}
