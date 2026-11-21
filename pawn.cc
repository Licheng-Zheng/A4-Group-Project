#include "pawn.h"
#include "piece.h"
#include <vector> 
using namespace std; 


Pawn::Pawn(int colour, Position pos) {  // sets its own position. Constructs it so that it is at this position. 
    // created elsewhere, just need to set the information now 

    this -> colour = colour; 
    
    // Need to create a copy function for position for this to work
    this -> Position = Position; 
}

// need to create the move class as well
vector<Move> Pawn::(const Board &board) const {
    // this needs to simulate all the possible moves for the piece to do, then check if it results in a position that is not doable

} 


char Pawn::getSymbol() const {
    if (colour == 1) {
        return 'p"' 
    }
    return 'P'; 
}
