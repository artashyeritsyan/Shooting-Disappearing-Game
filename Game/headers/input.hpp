#ifndef INPUT_HPP
#define INPUT_HPP

#include <ncurses.h>

#include "enums.hpp"

class Input {
public:

    // enum EControls {
    //     up,
    //     down,
    //     left,
    //     right,
    //     exit
    // };

    EControls inputHandling();
};

#endif // INPUT_HPP