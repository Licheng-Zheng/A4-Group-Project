#ifndef COMMANDINTERPRETER_H
#define COMMANDINTERPRETER_H
#include <ostream>
#include <sstream>
#include <string>
#include "game.h"

class Commandinterpreter {
    Game *game;
    whiteScore double;
    blackScore double;
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
        void start()
        void printScore(std::ostream &out) const;
};
#endif