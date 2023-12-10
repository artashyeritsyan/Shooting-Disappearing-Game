#pragma once

#include <chrono>
#include <iostream>

#include "board.hpp"
#include "screen.hpp"
#include "scoreManager.hpp"

using SteadyClock = std::chrono::steady_clock;
using TimePoint = std::chrono::time_point<SteadyClock>; 

class Game {
private:
    Board board;
    GameScreen screen;
    ScoreManager scoreManager;
    
    const std::chrono::milliseconds rowGenerationTime{4500};    
    const std::chrono::milliseconds bulletMovingTime{25};
    const std::chrono::milliseconds shotCooldownTime{100};

    TimePoint rowGenerationStartTime;
    TimePoint bulletMovingStartTime;
    TimePoint shotCooldownStartTime;

    int cursorX;
    int cursorY;

    int scoreAmount = 100;
    
public:
    Game();
    ~Game();
    void start();
    void cooldownManager();
    void shootManager();
    void inputHandling();
};