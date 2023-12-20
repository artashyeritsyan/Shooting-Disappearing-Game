#include "board.hpp"

Board::Board() {
    table[0] = generateRow();    
}

matrixOfCube Board::getTable() {
    return table;
}

arrayOfCube Board::generateRow() {
    srand(time(NULL));
    arrayOfCube randomFilledRow;

    int minRange = BOARD_WIDTH / 3;
    int maxRange = BOARD_WIDTH / 3 * 2;
    int pixelsCount = (rand() % (maxRange - minRange + 1)) + minRange;
    
    int position;
    for (int i = 0; i < pixelsCount; ++i)
    {
        do
        {
            position = rand() % BOARD_WIDTH;
        } while (randomFilledRow[position].getBlock() == true);
        randomFilledRow[position].setBlock(true);
    }

    return randomFilledRow;
}

bool Board::checkLossStatus() {
    for(int i = 0; i < BOARD_WIDTH; ++i) {
        if(table[BOARD_HEIGHT - 3][i].getBlock() && !table[BOARD_HEIGHT - 3][i].getMovement()) {
            return true;
        }
    }
    return false;
}

void Board::addNewLine() {
    auto tempTable = table;

    int startRow = BOARD_HEIGHT - 3;
    int endRow = 0;
    
    while (startRow > endRow)
    {
        for (int i = 0; i < BOARD_WIDTH; ++i)
        {
            table[startRow][i] = tempTable[startRow - 1][i];
        }
        --startRow;
    }

    auto generatedRow = generateRow();
    for (int i = 0; i < BOARD_WIDTH; ++i)
    {
        table[0][i] = generatedRow[i];
        table[0][i].setMovement(false);
    }
}

void Board::shoot(int cursorX) {
    int bulletIndexY = BOARD_HEIGHT - 3;
    const int bulletIndexX = cursorX;

    if(!table[bulletIndexY][bulletIndexX].getBlock()){
        table[bulletIndexY][bulletIndexX].setMovement(true);
        table[bulletIndexY][bulletIndexX].setBlock(true);
    }
}

void Board::updatePlayerPosition(int positionX, int positionY) {
    for (int i = BOARD_HEIGHT - 2; i < BOARD_HEIGHT; ++i) {
        for (int j = 0; j < BOARD_WIDTH; ++j) {
            table[i][j].setBlock(false);
        }
    }

    table[positionY][positionX].setBlock(true);
    table[positionY - 1][positionX].setBlock(true);

    if (positionX != BOARD_WIDTH - 1)
        table[positionY][positionX + 1].setBlock(true);
    if (positionX != 0)
        table[positionY][positionX - 1].setBlock(true);
}

void Board::moveBulletsUp() {
    for (int i = 0; i < BOARD_HEIGHT - 2; ++i)
    {
        for (int j = 0; j < BOARD_WIDTH; ++j)
        {
            if (table[i][j].getMovement())
            {
                if (i - 1 >= 0 && (!table[i - 1][j].getBlock()))
                {
                    table[i - 1][j].setBlock(true);
                    table[i][j].setBlock(false);

                    table[i][j].setMovement(false);

                    if (i - 2 >= 0 && (!table[i - 2][j].getBlock() || 
                    (table[i - 2][j].getBlock() && table[i - 2][j].getMovement())) )
                    {
                        table[i - 1][j].setMovement(true);
                    }
                }
                else
                {
                    table[i][j].setMovement(false);
                }
            }
        }
    }
}

bool Board::checkToDestroyLine() {
    for (int i = 0; i < BOARD_HEIGHT; ++i)
    {   
        bool isLineFull = true;
        for (int j = 0; j < BOARD_WIDTH; ++j)
        {
            if (!table[i][j].getBlock() || table[i][j].getMovement()) {
                isLineFull = false;
                continue;
            }
        }

        if (isLineFull) {
            destroyLine(i);
            return true;
        }        
    }
    return false;
}

void Board::destroyLine(int lineIndex) {
    auto tempTable = table;

    int startRow = lineIndex;
    int endRow = BOARD_HEIGHT - 3;

    while (startRow < endRow)
    {
        for (int i = 0; i < BOARD_WIDTH; ++i)
        {
            table[startRow][i] = tempTable[startRow + 1][i];
        }
        ++startRow;
    }

    for(int i = 0; i < BOARD_WIDTH; ++i) {
        table[endRow][i].setBlock(false);
        table[endRow][i].setMovement(false);
    }
}
