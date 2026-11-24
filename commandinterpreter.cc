#include <ostream>
#include <sstream>
#include "commandinterpreter.h"
#include <memory>
#include "king.h"
#include "queen.h"
#include "rook.h"
#include "bishop.h"
#include "knight.h"
#include "pawn.h"

Commandinterpreter::Commandinterpreter() : game{nullptr}, whiteScore{0}, blackScore{0}, startTurn(0) { startBoard.initDefaultBoard(); }

Commandinterpreter::~Commandinterpreter() {delete game;}

//used in setup to create pieces
std::unique_ptr<Piece> createPiece(char c, Position p) {
    int colour = (c >= 'a' && c <= 'z') ? 1:0;
    //switches black to uppercase otherwise its already uppercased
    char uppercase = (colour == 1) ? c - 'a' + 'A' : c;
    if (uppercase == 'K') return std::make_unique<King>(colour, p);
    if (uppercase == 'Q') return std::make_unique<Queen>(colour, p);
    if (uppercase == 'R') return std::make_unique<Rook>(colour, p);
    if (uppercase == 'B') return std::make_unique<Bishop>(colour, p);
    if (uppercase == 'N') return std::make_unique<Knight>(colour, p);
    if (uppercase == 'P') return std::make_unique<Pawn>(colour, p);
    return nullptr;
}

void Commandinterpreter::start(std::istream &in, std::ostream &out) {
    std::string s;
    while (std::getline(in,s)) {
        std::istringstream args{s};
        std::string command;
        if (!(args >> command)) continue; //checks for empty lines - goes to next iteration if empty

        //checks the command and runs the approiate functions
        if (command == "game") {
            beginGame(args, out);
        } else if (command == "move") {
            makeMove(args, out);
        } else if (command == "resign") {
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
            out << "Invalid command: " << command << std::endl;
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
    game = new Game{white, black, startBoard, startTurn, out};
    startBoard.initDefaultBoard();
    startTurn = 0;
}

void Commandinterpreter::makeMove(std::istream &args, std::ostream &out) {
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
        out << "Invalid position" << std::endl;
        return;
    }

    //check for promotion
    std::string promo;
    if (args >> promo) {
        char p = promo[0];
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
            char c = (piece.length() == 1) ? piece[0] : ' ';
            if (!(c == 'Q' || c == 'R' || c == 'B' || c == 'N' || c == 'K' || c == 'P' || c == 'k' || c == 'p' || c == 'q' || c == 'r' || c == 'b' || c == 'n') || !p.isValid()) {
                out << "Invalid Input - Please use: + (piece) (square)" << std::endl;
                continue;
            }
            startBoard.placePiece(createPiece(c,p), p);
            out << startBoard;
        } else if (command == "-") {
            std::string square;
            args >> square;
            Position p = Position::convert(square);
            if (!p.isValid()) {
                out << "Invalid input - Please use: - (square)" << std::endl;
                continue;
            }
            startBoard.removePiece(p);
            out << startBoard;
        } else if (command == "=") {
            std::string colour;
            args >> colour;
            if (colour != "white" && colour != "black") {
                out << "Invalid input - Please use: = (white or black)" << std::endl;
                continue;
            }
            startTurn = (colour == "white") ? 0 : 1;
        } else if (command == "done") {
        out << "Ending setup mode" << std::endl;
        return;
        } else {
        out << "Invalid setup command: " << command << std::endl;
        }
    }
}


void Commandinterpreter::checkEnd() {
    if (!game) return;
    int state = game->getState();
    if (state == PLAYING) return;
    if (state == W_Win) whiteScore += 1;
    else if (state == B_Win) blackScore += 1;
    else if (state == DRAW) {
        whiteScore += 0.5;
        blackScore += 0.5;
    }
    delete game;
    game = nullptr;
}

bool Commandinterpreter::isValid(const std::string &p) const { return p == "human" || p == "computer1" || p == "computer2" || p == "computer3" || p == "computer4"; }

void Commandinterpreter::printScore(std::ostream &out) const {
    out << "Final Score:" << std::endl;
    out << "White: " << whiteScore << std::endl;
    out << "Black: " << blackScore << std::endl;
}