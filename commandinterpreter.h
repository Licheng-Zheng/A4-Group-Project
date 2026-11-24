#ifndef COMMANDINTERPRETER_H
#define COMMANDINTERPRETER_H
#include <iostream>
#include <sstream>
#include <string>
#include "game.h"
#include "board.h"

class Commandinterpreter {
    Game *game;
    double whiteScore;
    double blackScore;
    Board startBoard;
    int startTurn;
    //Starts up a new game
    void beginGame(std::istream &args, std::ostream &out);

    //For when user types a move
    void makeMove(std::istream &args, std::ostream &out);

    //For when user requests setup
    void setup(std::istream &in, std::ostream &out);

    void checkEnd();

    bool isValid(const std::string &player) const;

    public:
        Commandinterpreter();
        ~Commandinterpreter();
        //Start the actual chess session
        void start(std::istream &in, std::ostream &out);
        void printScore(std::ostream &out) const;
};
#endif