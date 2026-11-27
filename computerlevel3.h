#ifndef COMPUTERLEVEL3_H
#define COMPUTERLEVEL3_H

#include <vector>
#include "move.h"

// calculates how "good" a move is
struct MoveEvaluation {
    Move move;
    bool isSafe;
    bool givesCheck;
};

// the level 3 bot will pick the move with the highest score
Move chooseLevel3(const std::vector<MoveEvaluation> &evaluations);

#endif
