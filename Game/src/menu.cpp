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
    int buttonsCount = 4;

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
            if (highlight < buttonsCount - 1) {
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