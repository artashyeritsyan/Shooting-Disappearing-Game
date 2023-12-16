#ifndef BOARD_HPP
#define BOARD_HPP

#include <array>
#include <iostream>

#include "cube.hpp"

static const int boardHeight = 20;
static const int boardWidth = 10;

using arrayOfCube = std::array<Cube, boardWidth>;
using matrixOfCube = std::array<arrayOfCube, boardHeight>;

class Board {
private:
    bool isLose = false;
    matrixOfCube table;
    void destroyLine(int lineIndex);

public:
    Board();
    ~Board();
    void shoot(int cursorX);
    void moveBulletsUp();
    bool checkToDestroyLine();
    void addNewLine();
    void destructionAnimation(int lineIndex);
    void updatePlayerPosition(int positionX, int positionY);
    std::array<Cube, boardWidth> generateRow();
    matrixOfCube getTable();
    bool getIsLose();
};

#endif // BOARD_HPP