#ifndef MOVE_H
#define MOVE_H

struct Move {
    Position prev; //position before move
    Position next; //position after move

    char promotion;
    bool isCapture;

    Move() : promotion{''}, isCapture{false} {}
};

#endif