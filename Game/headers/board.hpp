#ifndef BOARD_HPP
#define BOARD_HPP

#include <array>
#include <iostream>

#include "cube.hpp"

const int BOARD_HEIGHT = 20;
const int BOARD_WIDTH = 10;

using arrayOfCube = std::array<Cube, BOARD_WIDTH>;
using matrixOfCube = std::array<arrayOfCube, BOARD_HEIGHT>;

class Board {
public:
    Board();
    void shoot(int cursorX);
    void moveBulletsUp();
    bool checkToDestroyLine();
    void addNewLine();
    void updatePlayerPosition(int positionX, int positionY);
    arrayOfCube generateRow();
    matrixOfCube getTable();
    bool checkLossStatus();

private:
    matrixOfCube table;
    void destroyLine(int lineIndex);
};

#endif // BOARD_HPP