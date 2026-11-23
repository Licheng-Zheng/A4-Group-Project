#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <string>
#include "move.h"

const int PLAYING = 0;
const int W_Win = 1;
const int B_Win = 2;
const int DRAW = 3;

class Game {
    std::string white;
    std::string black;
    int colour;
    int state;
    std::ostream &out;

    public:
        Game(const std::string &white, const std::string &black, std::ostream &out);

        bool move(const Move&m);
        void endGame();
        int getState() const;
        int getTurn() const;
};

#endif