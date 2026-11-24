#ifndef BOARD_H 
#define BOARD_H 

#include <iostream> 
#include <memory> 

using namespace std; 

// will need to figure out the move, piece, position and other classes and what is required

// the class for board, things are declared here
class Board {
    // unique_ptr comes from the memory library. Piece is an abstract class, so we can't create objects
    // we are using polymorphism here, where we refer to the piece by its base class. 
    unique_ptr<Piece> chessBoard[8][8]; 

public: 
    Board();
    ~Board();

    // the copy operator, we need this so we can create a board, try out a move, see if its valid without overwriting anything
    Board(const Board &other);

    // fills out the board with the starting position
    void initDefaultBoard();

    // we can try to create a function that takes in the moves to get into a position, it runs through it, and then it creates that as the board

    // moves a piece to another position
    void placePiece(std::unique_ptr<Piece> piece, Position pos);

    // sets piece at the position to 0 
    void removePiece(Position pos);

    bool isValidSetup() const;

    // check if the move can be performed (we need to figure out the move first) 
    bool movePiece(Move m, int turn);
    bool isLegalMove(Move m, int player) const;

    // Figure out a way to have a list of all the possible moves. 

    bool isInCheck(int player) const;
    bool isCheckmate(int player) const;
    bool isStalemate(int player) const;
    bool isSquareAttacked(Position pos, Colour byPlayer) const;

    // helpoer functions
    const Piece *getPieceAt(Position pos) const;
    Position getEnPassantTarget() const;

    // this is called by the << operator
    void print(std::ostream &out) const;
};

std::ostream &operator<<(std::ostream &out, const Board &b);

#endif
