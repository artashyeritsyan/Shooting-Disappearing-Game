#ifndef MENU_HPP
#define MENU_HPP

#include "game.hpp"
#include "input.hpp"
#include "screen.hpp"

class Menu {
public:
    Menu();
    int menuButtons(Input input);
    void handleChoice(int choice);

    enum MenuOption {
        Play,
        Settings,
        Help,
        Exit
    };

private:
    MenuScreen menuScreen;
};

#endif // MENU_HPP