#ifndef MOVE_H
#define MOVE_H
#include "position.h"

struct Move {
    Position prev; //position before move
    Position next; //position after move

    char promotion;
    bool isCapture;

    Move() : promotion{'\0'}, isCapture{false} {}
};

#endif