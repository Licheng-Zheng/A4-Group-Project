#include "computerlevel1.h"
#include <cstdlib>
#include <stdexcept>

Move chooseLevel1(const std::vector<Move> &legalMoves) {
	// no legal moves
   if (legalMoves.empty()) {
        throw std::runtime_error("No legal moves");
    }
// picks a random move
    int index = rand() % legalMoves.size();
    return legalMoves[index];
}
