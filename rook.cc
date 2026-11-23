#include "rook.h"
#include "piece.h"
#include <vector> 
using namespace std; 


Rook::Rook(int colour, Position pos) {  // sets its own position. Constructs it so that it is at this position. 
    // created elsewhere, just need to set the information now 

    this -> colour = colour; 
    
    // Need to create a copy function for position for this to work
    this -> Position = Position; 
}

// need to create the move class as well
vector<Move> Rook::getValidMoves(const Board &board) const {
    // this needs to simulate all the possible moves for the piece to do, then check if it results in a position that is not doable
 // this needs to simulate all the possible moves for the piece to do, then check if it results in a position that is not doable

    // this is the thing that will be returned later 
    vector<Move> moves; 

    // so there isn't an isCheck loop, we just put everything into a vector and clean it up afterwards based on what results in us getting in check

    // the starting position 
    Position start = getPosition(); 

    int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}}; 

    for (int i=0; i<4; i++) {
        int row_change = directions[i][0]; 
        int col_change = directions[i][1]; 

        int new_r = start.row + row_change; 
        int new_c = start.col + col_change; 

        // stay within the board, doesn't hit another piece of the same color. 0 indexing, so it goes from 0 to 7 
        while (new_r>=0 && new_r <8 && new_c>=0 && new_c <8) {
            Position new_pos{new_r, new_c}; 
            const Piece *occupant = board.getPieceAt(target); 

            // if we hit our own colour do not add it as a possible position. 
            if (occupant != nullptr && occupant->getColour() == this -> getColour()) {
                break;
            }

            Move possibleMove{start, target}; 
            Board temporaryBoard = board; 

            // remove the piece at the current position 
            temporaryBoard.removePiece(start); 

            // add in our piece into the new position (in case the new position also blocks a check at the original piece blocks)
            temporaryBoard.placePiece(this, target);

            // THE IS IN CHECK CANNOT CALL THE BISHOP VALID MOVES OR ELSE THERE WILL BE A LOOP
            if (!temporaryBoard.isInCheck(this -> getColour())) {
                // if hte move doesn't put us into check then it is a valid move
                moves.push_back(possibleMove); // the move works
            }

            if (occupant != nullptr) {
                // if the occupant is an enemy piece, then we can capture it (we've already added it). BUT cannot go any further. 
                break; 
            }

            new_r++; 
            new_c++; 
        }
        return moves;
    }
    

} 


char Rook::getSymbol() const {
    if (colour == 1) {
        return 'r'; 
    }
    return 'R'; 
}
