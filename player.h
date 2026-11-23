#ifndef PLAYER_H
#define PLAYER_H

#include "move.h"

class Board;

class Player {
protected:
    int colour; // 0 is white 1 is back

public:
    Player(int colour);
    virtual ~Player() = default;

    int getColour() const;

    // humans and bots dont choose moves the same way
    virtual Move chooseMove(const Board &board) = 0;
};

#endif
