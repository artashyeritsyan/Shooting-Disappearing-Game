#include "cube.hpp"

Cube::Cube() 
{
    this->isBlock = false;
    this->isMoving = false;
}

bool Cube::getBlock() {
    return this->isBlock;
}

void Cube::setBlock(bool isBlock) {
    this->isBlock = isBlock;
}

bool Cube::getMovement() {
    return this->isMoving;
}

void Cube::setMovement(bool isMoving) {
    this->isMoving = isMoving;
}