#include "menu.hpp"

Menu::Menu() {

    while (true)
    {
        handleChoice(menuButtons());
    }
}

int Menu::menuButtons() {
    int choice;
    int highlight = 0;
    menuScreen.updateMenuWindow(highlight);

    while (true) {
        switch (choice) 
        {
        case KEY_UP:
            if (highlight > 0) {
                --highlight;
            }
            break;

        case KEY_DOWN:            
            if (highlight < 3) {
                ++highlight;
            }
            break;

        case 10:
            return highlight;
        default:
            break;
        }
    }
} 

void Menu::handleChoice(int choice) {
    switch (choice) 
        {
        case 0:
            Game game;
            game.start(); //TODO: this function must be return 1 or 0 (Restart or Menu)
            // Call restart function if 1 
            break;

        case 1:            
            if (highlight < 3) {
                ++highlight;
            }
            break;

        case 2:
            return highlight;
            break;

        case 3:
            break;

        default:
        }
}