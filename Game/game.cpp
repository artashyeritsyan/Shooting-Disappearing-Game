#include <curses.h>

class Cube {

private:
    int x, y;
    bool isMooving;

public:
    Cube(int x, int y, bool isMooving) : x(x), y(y), isMooving(isMooving) {}

    void draw(int color) {
        attron(COLOR_PAIR(color));
        mvprintw(y, x, "#");
        attroff(COLOR_PAIR(color));
    }

    print()

};