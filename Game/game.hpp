#include "board.hpp"
#include "screen.hpp"

class Game {
private:
    Board board;
    Screen screen;    
public:
    Game();
    ~Game();
    void start();    
};