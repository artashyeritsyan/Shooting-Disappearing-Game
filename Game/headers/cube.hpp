#ifndef CUBE_HPP
#define CUBE_HPP

class Cube {
public:
    Cube();
    bool getBlock();
    bool getMovement();
    void setBlock(bool);
    void setMovement(bool);

private:
    bool isBlock;
    bool isMoving;
};

#endif // CUBE_HPP