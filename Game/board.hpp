#include <array>
#include <iostream>

#include "cube.hpp"

static const int boardHeight = 20;
static const int boardWidth = 20;

class Board {
private:
    std::array<std::array<Cube, boardHeight>, boardWidth> table;
    void destroyLine(int lineIndex);

public:

    Board();    
    ~Board();
    void shoot(int cursorX);
    void moveBulletsUp();
    void checkToDestroyLine();
    void destructionAnimation(int lineIndex);
    void addNewLine();
    std::array<Cube, boardWidth> generateRow();
};