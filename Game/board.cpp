#include "board.hpp"

Board::Board() {
    table[0] = generateRow();    
}

Board::~Board() {

}

std::array<Cube, boardWidth> Board::generateRow() {
    std::array<Cube, boardWidth> randomFilledRow;

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
    
    for(int i = 0; i < boardWidth; ++i){
        if(table[boardHeight - 3][i].getBlock())
            return;
            //LOOSE FUNCTION (Mi ban pti mtacvi)
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
    }
}

void Board::shoot(int cursorX) {
    int bulletIndexY = boardHeight - 3;
    const int bulletIndexX = cursorX;

    table[bulletIndexY][bulletIndexX].setMovement(true);
    table[bulletIndexY][bulletIndexX].setBlock(true);
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

                    if (i - 2 >= 0 && (!table[i - 2][j].getBlock()))
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

    checkToDestroyLine();
}

void Board::checkToDestroyLine() {
    for (int i = 0; i < boardHeight; ++i)
    {
        for (int j = 0; j < boardWidth; ++j)
        {
            if (table[i][j].getBlock() && !table[i][j].getMovement()) {
                continue;
            }
        }

        destroyLine(i);
        break;
    }
}

void Board::destroyLine(int lineIndex) {
    auto tempTable = table;

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
    }

    destructionAnimation(lineIndex);
}

void Board::destructionAnimation(int lineIndex) {
    //TODO: create destrucion animation for line
}