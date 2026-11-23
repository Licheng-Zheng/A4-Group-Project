#include "king.h"
#include "piece.h"
#include <vector> 
using namespace std; 


King::King(int colour, Position pos) {  // sets its own position. Constructs it so that it is at this position. 
    // created elsewhere, just need to set the information now 

    this -> colour = colour; 
    
    // Need to create a copy function for position for this to work
    this -> Position = Position; 
}

// need to create the move class as well
vector<Move> King::getValidMoves(const Board &board) const {
    // this needs to simulate all the possible moves for the piece to do, then check if it results in a position that is not doable
    vector<Move> Knight::getValidMoves(const Board &board) const {
    // this needs to simulate all the possible moves for the piece to do, then check if it results in a position that is not doable

    // no need for a loop because it can go in a couple directions regardless 

    
        // this needs to simulate all the possible moves for the piece to do, then check if it results in a position that is not doable

    // this is the thing that will be returned later 
    vector<Move> moves; 

    // so there isn't an isCheck loop, we just put everything into a vector and clean it up afterwards based on what results in us getting in check

    // the starting position 
    Position start = getPosition(); 

    int directions[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {0, -1}, {1, 1}, {1, 0}, {1, -1}};



    for (int i=0; i<8; i++) {
        int row_change = directions[i][0]; 
        int col_change = directions[i][1]; 

        int new_r = start.row + row_change; 
        int new_c = start.col + col_change; 
        // outside
        
        if (!(new_r>=0 && new_r <8 && new_c>=0 && new_c <8)) {
            break;
        }

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
    }


    // CHECKING FOR CASTLING 
    // if hte king has moved, it cannot castle 
    if (!(this->getHasMoved())) {
        Position kingPos = this->getPosition();
        int kingColour = this->getColour();
        int opponent;
        int homeRow;
        char expectedRook;

        if (kingColour == 0) { // White
            opponent = 1;
            homeRow = 7;
            expectedRook = 'R'; //  R is the rook character expected
        } else {               // Black (1)
            opponent = 0;
            homeRow = 0;
            expectedRook = 'r';
        }

        // king can't be in check
        if (kingPos.row == homeRow && kingPos.col == 4 &&
            !board.isSquareAttacked(kingPos, opponent)) {

            Piece *farRook = board.getPieceAt(Position{kingPos.row, 0});
            if (farRook != nullptr &&
                farRook->getSymbol() == expectedRook &&
                !farRook->getHasMoved()) {

                // Columns 1, 2, 3 must be empty; King's path (cols 3 and 2) must not be attacked
                if (board.getPieceAt(Position{kingPos.row, 1}) == nullptr &&
                    board.getPieceAt(Position{kingPos.row, 2}) == nullptr &&
                    board.getPieceAt(Position{kingPos.row, 3}) == nullptr &&
                    !board.isSquareAttacked(Position{kingPos.row, 3}, opponent) &&
                    !board.isSquareAttacked(Position{kingPos.row, 2}, opponent)) {

                    moves.push_back(Move{kingPos, Position{kingPos.row, 2}});
                }
            }

            const Piece *closeRook = board.getPieceAt(Position{kingPos.row, 7});
            if (closeRook != nullptr &&
                closeRook->getSymbol() == expectedRook &&
                !closeRook->getHasMoved()) {

                // Columns 5 and 6 must be empty and not attacked
                if (board.getPieceAt(Position{kingPos.row, 5}) == nullptr &&
                    board.getPieceAt(Position{kingPos.row, 6}) == nullptr &&
                    !board.isSquareAttacked(Position{kingPos.row, 5}, opponent) &&
                    !board.isSquareAttacked(Position{kingPos.row, 6}, opponent)) {

                    moves.push_back(Move{kingPos, Position{kingPos.row, 6}});
                }
            }
        }
    }

    return moves; 
} 


char King::getSymbol() const {
    if (colour == 1) {
        return 'k'; 
    }
    return 'K"' 
}
