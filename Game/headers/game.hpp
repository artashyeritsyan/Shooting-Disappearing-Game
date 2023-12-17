#ifndef GAME_HPP
#define GAME_HPP

#include <chrono>
#include <iostream>

#include "board.hpp"
#include "enums.hpp"
#include "input.hpp"
#include "screen.hpp"
#include "scoreManager.hpp"

using SteadyClock = std::chrono::steady_clock;
using TimePoint = std::chrono::time_point<SteadyClock>; 

class Game {
public:
    Game();
    void start();
    void cooldownManager();
    void shootManager();
    void inputActions(EControls action);

private:
    Board board;
    GameScreen screen;
    ScoreManager scoreManager;

    bool lossStatus;
    int cursorX;
    int cursorY;

};

#endif // GAME_HPP