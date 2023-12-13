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

    while (true) {
        menuScreen.updateMenuWindow(highlight);
        choice = getch();
        
        switch (choice) 
        {
        case 'w':
            if (highlight > 0) {
                --highlight;
            }
            break;

        case 's':            
            if (highlight < 3) {
                ++highlight;
            }
            break;

        case 10:
            return highlight;
        }
    }
}


void Menu::handleChoice(int choice) {
    Game game;
    switch (choice) 
    {
    case Play:
        game.start();
        
        // Call Restart screen where will be Restart and MainMenu buttons
        // Call restart function if 1
        // and call menu screen when 0 
        break;

    case Settings:            
        
        break;

    case Help:

        break;

    case Exit:
        break;

    default:
        break;
    }

}