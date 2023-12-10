#include "board.hpp"

Board::Board() {
    table[0] = generateRow();    
}

Board::~Board() {

}

matrixOfCube Board::getTable() {
    return table;
}

bool Board::getIsLose() {
    return isLose;
}

arrayOfCube Board::generateRow() {
    srand(time(NULL));
    arrayOfCube randomFilledRow;

    int minRange = boardWidth / 3;
    int maxRange = boardWidth / 3 * 2;
    int pixelsCount = (rand() % (maxRange - minRange + 1)) + minRange;
    
    int position;
    for (int i = 0; i < pixelsCount; ++i)
    {
        do
        {
            position = rand() % boardWidth;
        } while (randomFilledRow[position].getBlock() == true);
        randomFilledRow[position].setBlock(true);
    }

    return randomFilledRow;
}

void Board::addNewLine() {
    
    for(int i = 0; i < boardWidth; ++i) {
        if(table[boardHeight - 3][i].getBlock() && !table[boardHeight - 3][i].getMovement()) {
            isLose = true;
        }
    }

    auto tempTable = table;

    int startRow = boardHeight - 3;
    int endRow = 0;
    
    while (startRow > endRow)
    {
        for (int i = 0; i < boardWidth; ++i)
        {
            table[startRow][i] = tempTable[startRow - 1][i];
        }
        --startRow;
    }

    auto generatedRow = generateRow();
    for (int i = 0; i < boardWidth; ++i)
    {
        table[0][i] = generatedRow[i];
        table[0][i].setMovement(false);
    }
}

void Board::shoot(int cursorX) {
    int bulletIndexY = boardHeight - 3;
    const int bulletIndexX = cursorX;

    table[bulletIndexY][bulletIndexX].setMovement(true);
    table[bulletIndexY][bulletIndexX].setBlock(true);
}

void Board::updatePlayerPosition(int positionX, int positionY) {
    for (int i = boardHeight - 2; i < boardHeight; ++i) {
        for (int j = 0; j < boardWidth; ++j) {
            table[i][j].setBlock(false);
        }
    }

    table[positionY][positionX].setBlock(true);
    table[positionY - 1][positionX].setBlock(true);

    if (positionX != boardWidth - 1)
        table[positionY][positionX + 1].setBlock(true);
    if (positionX != 0)
        table[positionY][positionX - 1].setBlock(true);
}

void Board::moveBulletsUp() {
    for (int i = 0; i < boardHeight - 2; ++i)
    {
        for (int j = 0; j < boardWidth; ++j)
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
    bool isLineFull = true;
    for (int i = 0; i < boardHeight; ++i)
    {   
        isLineFull = true;
        for (int j = 0; j < boardWidth; ++j)
        {
            if (!table[i][j].getBlock() || table[i][j].getMovement()) {
                isLineFull = false;
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
    ///
    for(int i = 0; i < boardWidth; ++i) {
        table[10][i].setBlock(true);
    }

    int startRow = lineIndex;
    int endRow = boardHeight - 3;

    while (startRow < endRow)
    {
        for (int i = 0; i < boardWidth; ++i)
        {
            table[startRow][i] = tempTable[startRow + 1][i];
        }
        ++startRow;
    }

    for(int i = 0; i < boardWidth; ++i) {
        table[endRow][i].setBlock(false);
        table[endRow][i].setMovement(false);
    }

    destructionAnimation(lineIndex);
}

void Board::destructionAnimation(int lineIndex) {
    //TODO: create destrucion animation for line
}