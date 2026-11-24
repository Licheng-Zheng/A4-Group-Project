#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <string>
#include "move.h"
#include "board.h"

const int PLAYING = 0;
const int W_Win = 1;
const int B_Win = 2;
const int DRAW = 3;

class Game {
    Board board;
    std::string white;
    std::string black;
    int colour;
    int state;
    std::ostream &out;

    //prints out checks and checkmates,etc (DOES NOT CHECK FOR THEM, USES THE CHECK FUNCTION TO PRINT STATUS)
    void printStatus();

    public:
        Game(const std::string &white, const std::string &black, const Board &start, int firstTurn, std::ostream &out);

        bool move(const Move&m);
        void endGame();
        int getState() const;
        int getTurn() const;
};

#endif