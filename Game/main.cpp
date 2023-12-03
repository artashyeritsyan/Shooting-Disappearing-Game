#include <ncurses.h>
#include <cmath>

int main() {
    // Initialize ncurses
    initscr();
    cbreak(); // Disable line buffering
    noecho(); // Do not display input characters
    keypad(stdscr, TRUE); // Enable special keys

    int gameScreenHeight, gameScreenwidth;
    gameScreenHeight = 10; // Set screen gameScreenHeight to 10
    gameScreenwidth = 10;  // Set screen gameScreenwidth to 10
    WINDOW *win = newwin(gameScreenHeight, gameScreenwidth, 0, 0); // Create a window

    int x = gameScreenwidth / 2; // Initial x position in the middle of the screen
    int y = gameScreenHeight / 2; // Initial y position in the middle of the screen

    int ch;

    // Draw a box around the window
    box(win, 0, 0);

    // Move the cursor to the initial position
    move(y, x);
    refresh();

    // Process user input
    while ((ch = getch()) != 'q') {
        // Check for arrow keys
        switch (ch) {
            case KEY_RIGHT:
                // Move right
                x++;
                break;
            case KEY_LEFT:
                // Move left
                x--;
                break;
        }

        // Ensure the cursor stays within the window
        x = std::max(1, std::min(x, gameScreenwidth - 2));
        y = std::max(1, std::min(y, gameScreenHeight - 2));

        // Clear the window
        werase(win);

        // Draw a box around the window
        box(win, 0, 0);

        // Move the cursor to the new position
        wmove(win, y, x);

        // Refresh the window
        wrefresh(win);
    }

    // Clean up and exit
    delwin(win);
    endwin();

    return 0;
}
