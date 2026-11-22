#include <ostream>
#include <sstream>
#include "commandinterpreter.h"

Commandinterpreter::Commandinterpreter() : game{nullptr}, whiteScore{0}, blackScore{0} {}

Commandinterpreter::~Commandinterpreter() {delete game;}

void Commandinterpreter::start(std::istream &in, std::ostream &out) {
    std::string s;
    while (std::getline(in,s)) {
        std::istringstream args{s};
        std::string command;
        if (!(args >> command)) continue; //checks for empty lines - goes to next iteration if empty

        //checks the command and runs the approiate functions
        if (command == "game") {
            startGame(args, out);
        } else if (command == "move") {
            move(args, out);
        } else if (commdnad == "resign") {
            if (!game) { //checks if theres a game running using its pointer
                out << "No game is running" << std::endl;
            } else {
                game->endGame();
                checkEnd();
            }
        } else if (command == "setup") {
            if (game) out << "Can't use setup while a game is running" << std::endl;
            else setup(in, out);
        } else {
            out << "Invalid command: " << commmand << std::endl;
        }
    }
    printScore(out);
}

void Commandinterpreter::beginGame(std::istream &args, std::ostream &out) {
    if (game) {
        out << "A game is already running" << std::endl;
        return;
    }
    std::string white, black;
    if (!(args >> white >> black) || !isValid(white) || !isValid(black)) {
        out << "Please use: game (human or computer1-4) (human or computer1-4)" << std::endl;
        return;
    }
    game = new Game{white, black, out};
}

void Commandinterpreter::move(std::istream &args, std::ostream &out) {
    if (!game) {
        out << "No game is running" << std::endl;
        return;
    }
    std::string prev;
    if (!(args >> prev)) {
        out << "no computer play yet" << std::endl;
        return;
    }
    //copies user's input into a position then set move m
    std::string next;
    args >> next;
    Move m;
    m.prev = Position::convert(prev);
    m.next = Position::convert(next);
    if (!m.prev.isValid() || !m.next.isValid()) {
        out << "Invalid position"
        return;
    }

    //check for promotion
    std::string promo;
    if (args >> promo) {
        if (promo.length() != 1 || !(p == 'Q' || p == 'R' || p == 'B' || p == 'N' || p == 'q' || p == 'r' || p == 'b' || p == 'n')) {
            out << "Not a valid promotion type" << std::endl;
            return;
        }
        m.promotion = promo[0];
    }
    if (!game -> move(m)) out << "Illegal move" << std::endl;
    checkEnd();
}

void Commandinterpreter::setup(std::istream &in, std::ostream &out) {
    out << "Starting setup mode" << std::endl;
    std::string s;
    while (std::getline(in, s)) {
        std::istringstream args{s};
        std::string command;
        if (!(args >> command)) continue;
        //Bunch of setup command checkings
        if (command == "+") {
            std::string piece, square;
            args >> piece >> square;
            Position p = Position::convert(square);
            if (piece.length() != 1 || !p.isValid()) {
                if (promo.length() != 1 || !(p == 'Q' || p == 'R' || p == 'B' || p == 'N' || p == 'q' || p == 'r' || p == 'b' || p == 'n')) {
                    out << "Invalid Input - Please use: + (piece) (square)" << std::endl;
                    continue;
                }
                out << "placed " << piece << " on " << p.toString() << std::endl;
            }
        } else if (command == "-") {
            std::string square;
            args >> sqaure;
            Position p = Position::convert(square);
            if (!p.isValid()) {
                out << "Invalid input - Please use: - (square)" << std::endl;
                continue;
            }
            out << "removed piece on " << p.toString() << std::endl;
        } else if (command == "=") {
            std::string colour;
            args >> colour;
            if (colour != "white" && colour != "black") {
                out << "Invalid input - Please use: = (white or black)" << std::endl;
                continue;
            }
            out << colour << "moves first" << std::endl;
        }
    } else if (command == "done") {
        out << "Ending setup mode" << std::endl;
        return;
    } else {
        out << "Invalid setup command: " << command << std::endl;
    }
}

void Commandinterpreter::checkEnd() {
    if (!game) return;
    int state = game->getState();
    if (r == PLAYING) return;
    if (r == W_Win) whiteScore += 1;
    else if (r == B_Win) blackScore += 1;
    else if (r == DRAW) {
        whiteScore += 0.5;
        blackScore += 0.5;
    }
    delete game;
    game = nullptr;
}

bool CommandInterpreter::isValid(const std::string &p) const { return p == "human" || p == "computer1" || p == "computer2" || p == "computer3" || p == "computer4"; }

void CommandInterpreter::printScore(std::ostream &out) const {
    out << "Final Score:" << std::endl;
    out << "White: " << whiteScore << std::endl;
    out << "Black: " << blackScore << std::endl;
}