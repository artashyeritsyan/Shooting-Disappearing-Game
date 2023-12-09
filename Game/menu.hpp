#pragma once

#include "game.hpp"
#include "screen.hpp"

class Menu {
private:
    MenuScreen menuScreen;

    const char* buttons[4] = {
        "Play",
        "Settings",
        "Help",
        "Exit",
    };

public:
    Menu();
    int menuButtons();
    void handleChoice(int choice);


    enum MenuOption {
    Play,
    Settings,
    Help,
    Exit
};
};