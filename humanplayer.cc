#include "humanplayer.h"

// ctor
HumanPlayer::HumanPlayer(int colour) : Player{colour} {}

void HumanPlayer::setMove(const Move &move) {
    selectedMove = move;
}

Move HumanPlayer::chooseMove(const Board &board) {
    (void)board;
    return selectedMove;
}
