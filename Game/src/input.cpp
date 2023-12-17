#include "input.hpp"

EControls Input::inputHandling() {
    int inputKey;
    inputKey = getch();

    switch (inputKey)
    {
    case KEY_UP:
    case 'w':
    case ' ':
        return up;
        break;

    case KEY_DOWN:
    case 's':
        return down;
        break;

    case KEY_LEFT:
    case 'a':
        return left;
        break;

    case KEY_RIGHT:
    case 'd':
        return right;
        break;

    case 10:
        return enter;
        break;

    case 'q':
    case 'Q':
        return quit;
        break;

    default:
        return null;
        break;
    }
}