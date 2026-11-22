#include "game.h"

Game::Game(const std::string &white, const std::string &black, std:: ostream &out) : white{white}, black{black}, colour{0}, state{PLAYING} , out{out} {
    out << "new game: " << white << " (white) vs " << black << " (black)" << std::endl;
}

bool Game::move(const Move &m) {
    out << (colour ? "white" : "black") << " moves " << m.from.toString() << " -> " << m.to.toString(); << std::endl;
    colour = colour ? 1 : 0;
    return true;
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

int Game::getTurn() const {return turn;}