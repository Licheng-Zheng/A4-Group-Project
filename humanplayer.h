#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "player.h"

class HumanPlayer : public Player {
    Move selectedMove;

public:
    HumanPlayer(int colour);

    void setMove(const Move &move);

    Move chooseMove(const Board &board) override;
};

#endif
