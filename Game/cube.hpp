#pragma once

class Cube {
private:
    bool isBlock;
    bool isMoving;
public:
    Cube();
    Cube(bool isBullet);
    ~Cube();
    bool getBlock();
    bool getMovement();
    void setBlock(bool);
    void setMovement(bool);
};