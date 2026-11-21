#ifndef KNIGHT_H
#define KNIGHT_H 

// the other pieces are just copies of this piece because nothing has its own functions (maybe castling and en passant?)

// need this so it can see the virtual functions that it needs to have here
#include "piece.h"
#include <vector> 
using namespace std; 

class Knight : public Piece {
public: 
    Knight(int colour, Position pos);  // sets its own position 
    // need to create the move class as well
    vector<Move> getValidMoves(const Board &board) const override; 
    // tells the compiler that this declaration is meant to override the virtual function defined in piece.h 

    char getSymbol() const override; 
}; 

#endif