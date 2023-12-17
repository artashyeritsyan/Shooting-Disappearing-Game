#ifndef CUBE_HPP
#define CUBE_HPP

class Cube {
private:
    bool isBlock;
    bool isMoving;

public:
    Cube();
    bool getBlock();
    bool getMovement();
    void setBlock(bool);
    void setMovement(bool);
};

#endif // CUBE_HPP