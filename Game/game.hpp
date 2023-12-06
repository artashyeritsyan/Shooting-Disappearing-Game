#pragma once
#include <chrono>
#include <iostream>
#include <thread>

#include "board.hpp"
#include "screen.hpp"

using SteadyClock = std::chrono::steady_clock;
using TimePoint = std::chrono::time_point<SteadyClock>; 

class Game {
private:
    Board board;
    
    const std::chrono::milliseconds rowGenerationTime{5000};    
    const std::chrono::milliseconds bulletMovingTime{100};
    const std::chrono::milliseconds shotCooldownTime{100};

    TimePoint rowGenerationStartTime;
    TimePoint bulletMovingStartTime;
    TimePoint shotCooldownStartTime;

    int cursorX;
    int cursorY;
    
public:
    Game();
    ~Game();
    void start();
    void cooldownManager();
    void shootManager();
    void inputHandling();
};