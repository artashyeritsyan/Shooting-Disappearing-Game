#include "menu.hpp"

Menu::Menu() {
    Input input;
    while (true)
    {
        input.inputHandling();
        handleChoice(menuButtons(input));
    }
}

int Menu::menuButtons(Input input) {
    int highlight = 0;

    while (true) {
        menuScreen.updateMenuWindow(highlight);
        
        switch (input.inputHandling()) 
        {
        case up:
            if (highlight > 0) {
                --highlight;
            }
            break;

        case down:            
            if (highlight < 3) {
                ++highlight;
            }
            break;

        case enter:
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
        std::exit(1);
        break;

    default:
        break;
    }

}