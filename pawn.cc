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

    // need completely custom code essentially because capturing and movement are different 
    vector<Move> moves; 
    vector<Position> possiblePositions; 

    Position start = getPosition(); 
    int myColour = getColour(); 

    int dir; 
    int startRow; 
    int promotionRow; 

    // setting up the information depending on where the items are
    if (myColour == 0) { 
        dir = -1;
        startRow = 6;
        promotionRow = 0;
    } else {
        dir = 1;
        startRow = 1;
        promotionRow = 7;
    }

    // checking if the pawn can move forward 
    int newRow = start.row + dir;
    if (newRow >= 0 && oneStepRow < 8) {
        Position oneStep{oneStepRow, start.col};

        // can only move onto an empty square (to move forward)
        if (board.getPieceAt(oneStep) == nullptr) {
            candidateTargets.push_back(oneStep);

            int twoStepRow = start.row + (2 * dir);
            if (!getHasMoved() && start.row == startRow && twoStepRow >= 0 && twoStepRow < 8) {
                Position twoStep{twoStepRow, start.col};
                // already checked if the space directly forward is clear for onestep
                if (board.getPieceAt(twoStep) == nullptr) {
                    candidateTargets.push_back(twoStep);
                }
            }
        }
    }

    // checking if the pawn can capture something 

    // the columns that captures can happen on 
    int captureRow = start.row + dir;
    int captureCols[2] = {start.col - 1, start.col + 1};

    for (int i = 0; i < 2; ++i) {
        int col = captureCols[i];

        // Make sure the diagonal square is on the 8x8 board
        if (captureRow >= 0 && captureRow < 8 && col >= 0 && col < 8) {
            Position target{captureRow, col};
            const Piece *occupant = board.getPieceAt(target);

            // Check if there is an enemy piece on that diagonal square
            if (occupant != nullptr && occupant->getColour() != myColour) {
                Board tempBoard = board;
                tempBoard.removePiece(start);
                tempBoard.placePiece(this->clone(), target);

                // Verify King safety before adding the capture
                if (!tempBoard.isInCheck(myColour)) {
                    if (target.row == promotionRow) {
                        char promoPieces[4] = {'Q', 'R', 'B', 'N'};
                        for (int j = 0; j < 4; ++j) {
                            moves.push_back(Move{start, target, promoPieces[j]});
                        }
                    } else {
                        moves.push_back(Move{start, target});
                    }
                }
            }
        }
    }
    
    // why is hte pawn the hardest one 

    Position epTarget = board.getEnPassantTarget();

    // right next to the poisition 
    if (epTarget.row >= 0 && epTarget.col >= 0 &&
        epTarget.row == start.row + dir &&
        (epTarget.col == start.col - 1 || epTarget.col == start.col + 1)) {

        // checking king safety 
        Board tempBoard = board;
        tempBoard.removePiece(start);
        tempBoard.removePiece(Position{start.row, epTarget.col}); 
        tempBoard.placePiece(this->clone(), epTarget);

        if (!tempBoard.isInCheck(myColour)) {
            moves.push_back(Move{start, epTarget});
        }
    }
    
    return Moves; 

    // FIGURE OUT HOW WE'RE GONNA GET PROMOPIECES TO WORK 
    // Need to figure out how we are representing promotions in the move class. 
    char promoPieces[4] = {'Q', 'R', 'B', 'N'};

} 


char Pawn::getSymbol() const {
    if (colour == 1) {
        return 'p"' 
    }
    return 'P'; 
}
