#ifndef m
#define m

struct Move {
    Position prev; //position before move
    Position next; //position after move

    bool isCapture;

    Move() : isCapture{false} {}
};

#endif