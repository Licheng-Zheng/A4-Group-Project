#ifndef MOVE_H
#define MOVE_H
#include "position.h"

struct Move {
    Position prev; //position before move
    Position next; //position after move

    char promotion;
    bool isCapture;

    Move(Position prev = Position{}, Position next = Position{}, char promotion = '\0') : prev{prev}, next{next}, promotion{promotion}, isCapture{false} {}
};

#endif