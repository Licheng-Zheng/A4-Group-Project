#ifndef PIECE_H
#define PIECE_H

#include <iostream>
#include <memory>
#include <vector>

using namespace std; 

class Piece { 
    int colour; // use an integer instead of a bool to represent the colour, allows for many different colors (0 = white 1 = black)
    
    Position pos; 
    // forgot why we needed a class for position

    bool hasMoved = false; // need to figure out a way to do this for presets (where we define the position), maybe just off the starting square? 

    int getColour() const; 
    Position getPosition() const; 
    void setPosition(Position newPos); 
    bool getHasMoved() const; 
    void setHasMoved(bool moved); // setter function 

    // a function to get the legal moves of the piece 
    // this is a virtual function, because it is defined by the moves that the piece can take
    virtual vector<Move> getValidMoves(const Board &board) const = 0; 
    // pure virtual function (cannot be called here, requires the board so that it can check things for like if the king is in check)

    virtual char getSymbol() const = 0; 
};

#endif 
