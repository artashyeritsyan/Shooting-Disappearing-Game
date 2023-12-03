#include <array>
#include <iostream>

#include "cube.hpp"

class Board {
private:
    static const int height = 20;
    static const int width = 20;

    std::array<std::array<Cube, height>, width> table;

public:
    
};