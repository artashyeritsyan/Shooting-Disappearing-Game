#pragma once

class Cube {
private:
    bool isBlock = false;
    bool isMoving = false;
public:
    Cube();
    Cube(bool isBullet);
    ~Cube();
    bool getBlock();
    bool getMovement();
    void setBlock(bool);
    void setMovement(bool );
};