#include "game.h"

Game::Game(const std::string &white, const std::string &black, const Board &start, int firstTurn, std:: ostream &out) : board{start}, white{white}, black{black}, colour{firstTurn}, state{PLAYING} , out{out} {
    out << board;
}

bool Game::move(const Move &m) {
    if (!board.movePiece(m, colour)) return false;
    out << board;
    colour = colour==0 ? 1 : 0;
    printStatus();
    return true;
}

void Game::printStatus() {
    std::string player = (colour == 0) ? "White" : "Black";
    std::string other = (colour == 0) ? "Black" : "White";

    if (board.isCheckmate(colour)) {
        out << "Checkmate! " << other << " wins!" << std::endl;
        state = (colour == 0) ? B_Win : W_Win;
    } else if(board.isStalemate(colour)) {
        out << "Stalemate!" << std::endl;
        state = DRAW;
    } else if(board.isInCheck(colour)) {
        out << player << " is in check." << std::endl;
    }
}

void Game::endGame() {
    if (colour == 0) {
        state = B_Win;
        out << "Black wins!" << std::endl;
    }  else {
        state = W_Win;
        out << "White wins!" << std::endl;
    }
}

int Game::getState() const { return state;}

int Game::getTurn() const {return colour;}