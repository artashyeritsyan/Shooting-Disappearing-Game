#ifndef GAME_HPP
#define GAME_HPP

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
    
    int gameSpeed = 4500;
    int speedCoefficient = 300;

    std::chrono::milliseconds rowGenerationTime{gameSpeed};
    const std::chrono::milliseconds bulletMovingTime{25};
    const std::chrono::milliseconds shotCooldownTime{160};
    const std::chrono::milliseconds speedUpTime{30000};

    TimePoint rowGenerationStartTime;
    TimePoint bulletMovingStartTime;
    TimePoint shotCooldownStartTime;
    TimePoint speedUpStartTime;

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

#endif // GAME_HPP