#include "board.h"
#include "king.h"
#include "queen.h"
#include "rook.h"
#include "bishop.h"
#include "knight.h"
#include "pawn.h"
#include <memory>
#include <string>
using namespace std;

Board::Board() {}

Board::~Board() {}

Board::Board(const Board &other) {
    for (int r = 0; r < 8; ++r) { // for each piece copy everything
        for (int c = 0; c < 8; ++c) {
            const Piece *p = other.chessBoard[r][c].get();
            if (!p) continue;  
            //copies everything
            char s = p->getSymbol();
            int colour = p->getColour();
            Position pos = p->getPosition();
            if (s == 'K' || s == 'k') chessBoard[r][c] = make_unique<King>(colour, pos);
            else if (s == 'Q' || s == 'q') chessBoard[r][c] = make_unique<Queen>(colour,pos);
            else if (s == 'R' || s == 'r') chessBoard[r][c] = make_unique<Rook>(colour, pos);
            else if (s == 'B' || s == 'b') chessBoard[r][c] = make_unique<Bishop>(colour, pos);
            else if (s == 'N' || s == 'n') chessBoard[r][c] = make_unique<Knight>(colour, pos);
            else chessBoard[r][c] = make_unique<Pawn>(colour, pos);
            chessBoard[r][c]->setHasMoved(p->getHasMoved());
        }
    }
}

void Board::initDefaultBoard() {
    for (int r = 0; r < 8; ++r) { //wipes out the board, saftey check for setup mode
        for (int c = 0; c < 8; ++c) {
            chessBoard[r][c] = nullptr;
        }
    }
    //places all the pieces
    this->placePiece(make_unique<Rook>(0, Position{0, 0}), Position{0,0});
    this->placePiece(make_unique<Knight>(0, Position{1, 0}), Position{1, 0});
    this->placePiece(make_unique<Bishop>(0, Position{2, 0}), Position{2, 0});
    this->placePiece(make_unique<Queen>(0, Position{3, 0}), Position{3, 0});
    this->placePiece(make_unique<King>(0, Position{4, 0}), Position{4, 0});
    this->placePiece(make_unique<Bishop>(0, Position{5, 0}), Position{5, 0});
    this->placePiece(make_unique<Knight>(0, Position{6, 0}), Position{6, 0});
    this->placePiece(make_unique<Rook>(0, Position{7, 7}), Position{7,7});
    this->placePiece(make_unique<Rook>(1, Position{0, 7}), Position{0,7});
    this->placePiece(make_unique<Knight>(1, Position{1, 7}), Position{1, 7});
    this->placePiece(make_unique<Bishop>(1, Position{2, 7}), Position{2, 7});
    this->placePiece(make_unique<Queen>(1, Position{3, 7}), Position{3, 7});
    this->placePiece(make_unique<King>(1, Position{4, 7}), Position{4, 7});
    this->placePiece(make_unique<Bishop>(1, Position{5, 7}), Position{5, 7});
    this->placePiece(make_unique<Knight>(1, Position{6, 7}), Position{6, 7});
    this->placePiece(make_unique<Rook>(1, Position{7, 7}), Position{7,7});
    //places pawns
    for (int c = 0; c < 8; ++c) {
        placePiece(make_unique<Pawn>(0, Position{c,1}), Position{c, 1});
        placePiece(make_unique<Pawn>(1, Position{c, 6}), Position{c, 6});
    }
}

void Board::placePiece(unique_ptr<Piece> piece, Position p) {
    if (!p.isValid()) return;
    if (piece) piece->setPosition(p);
    chessBoard[p.row][p.col] = std::move(piece); //deletes any piece already there and moves the new piece in
}

void Board::removePiece(Position p) {
    if (!p.isValid()) return;
    chessBoard[p.row][p.col] = nullptr;
}

const Piece* Board::getPieceAt(Position p) const {
    if (!p.isValid()) return nullptr;
    return chessBoard[p.row][p.col].get();
}

void Board::print(ostream& out) const {
    for (int r = 7; r >=0; --r) { //row top to bottom
        out << (r+1) << ' '; //prints num on the side
        for (int c = 0; c < 8; ++c) {//col left to right
            const Piece *p = chessBoard[r][c].get();
            if (p) out << p->getSymbol();
            else if ((r + c) % 2 == 0) out << "_"; //checks if its on board
            else out << ' ';
        }
        out << endl;
    }
    out << endl << " abcdefgh" << endl; //letter row at the bottom
}

// this is figured out elsewhere by the pawn logic and then put into here to be returned
Position Board::getEnPassantTarget() {
    return enPassantTarget; 
}

// Cannot call the valid moves for pieces because then its an infinite loop (they call this function)
bool Board::isSquareAttacked(Position pos, int theEnemy) {
    // theEnemy is same thing as colour
    // just checking if any of the pieces can hit this square 

    if (!pos.isValid()) return false; 


    // the row of the pawn that could attack this square
    int attackingPawnRow = 0; 
    // if the enemy is white. They attack upwards
    if (theEnemy == 0) {
        attackingPawnRow = pos.row - 1; 
    } else {
        // otherwise it is a black pawn that can attack it from a different dfirection
        attackingPawnRow = pos.row + 1; 
    }

    char pawnColour; 
    if (theEnemy == 0) {
        pawnColour = 'p'; // it is the other pawn colour that could attack this
    } else {
        pawnColour = 'P'; 
    }
    
    Position first{attackingPawnRow, pos.col - 1}; 
    if (getPieceAt(first) != nullptr && getPieceAt(first) == expectedPawn) {
        // the pawn is attacking the square
        return true; 
    } 

    Position second{attackingPawnRow, pos.col - 1}; 
    if (getPieceAt(second) != nullptr && getPieceAt(second) == expectedPawn) {
        // the pawn is attacking the square
        return true; 
    } 
    
    // checking for all of the possible knight attack s
    char knightColour; 
    if (theEnemy == 0) {
        pawnColour = 'n'; 
    } else {
        pawnColour = 'N'; 
    }

    int knight_squares[8][2] = {
        {-2, -1}, {-2, 1}, {-1, -2}, {-1, 2},
        { 1, -2}, { 1, 2}, { 2, -1}, { 2, 1}
    };

    for (int i = 0; i < 8; ++i) {
        Position to_be_attacked{pos.col + knight_squares[i][1], pos.row + knight_squares[i][0]};
        const Piece *p = getPieceAt(kPos);

        // if there is a bad knight at that position, then it is being attacked
        if (p != nullptr && p->getSymbol() == knightColour) {
            return true;
        }
    }

    // king attacks. 
    char kingColour;
    if (theEnemy == 0) {
        kingColour = 'K';
    } else {
        kingColour = 'k';
    }

    // king only covers the 8 things aroudn it 
    int king_squares[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, { 0, -1}, { 0, 1}, { 1, -1}, { 1, 0}, { 1, 1}};

    for (int i = 0; i < 8; ++i) {
        Position to_be_attacked{pos.col + king_squares[i][1], pos.row + king_squares[i][0]};
        const Piece *p = getPieceAt(to_be_attacked);

        if (p != nullptr && p->getSymbol() == kingColour) {
            return true;
        }
    }

    char rookColour;
    char queenColour;
    if (theEnemy == 0) {
        rookColour = 'R';
        queenColour = 'Q';
    } else {
        rookColour = 'r';
        queenColour = 'q';
    }

    int straight_dirs[4][2] = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1}
    };

    // rook and queen (only the straight lines for the queen, the diagonals checked with the bishop)
    for (int i = 0; i < 4; ++i) {
        int r = pos.row + straight_dirs[i][0];
        int c = pos.col + straight_dirs[i][1];

        while (r >= 0 && r < 8 && c >= 0 && c < 8) {
            Position current{c, r};
            const Piece *p = getPieceAt(current);

            if (p != nullptr) {
                // if the first piece along the line is the enemies rook or queen, then it is hitting the spot, stops checking afterwards because that means it is blocked (if it is blocked by something else)
                if (p->getSymbol() == rookColour || p->getSymbol() == queenColour) {
                    return true;
                }
                break;
            }

            // check the next piece
            r += straight_dirs[i][0];
            c += straight_dirs[i][1];
        }
    }

    // checking the diagonals for the bishop and queen
    char bishopColour;
    if (theEnemy == 0) {
        bishopColour = 'B';
    } else {
        bishopColour = 'b';
    }

    int diag_dirs[4][2] = {
        {-1, -1}, {-1, 1}, {1, -1}, {1, 1}
    };

    for (int i = 0; i < 4; ++i) {
        int r = pos.row + diag_dirs[i][0];
        int c = pos.col + diag_dirs[i][1];

        while (r >= 0 && r < 8 && c >= 0 && c < 8) {
            Position current{c, r};
            const Piece *p = getPieceAt(current);

            if (p != nullptr) {
                // bishops and queen diagonals. Only needs to check until it gets blocked or something is damaging it
                if (p->getSymbol() == bishopColour || p->getSymbol() == queenColour) {
                    return true;
                }
                break;
            }

            r += diag_dirs[i][0];
            c += diag_dirs[i][1];
        }
    }

    // nothing is attacking it FINALLY
    return false;
}

bool Board::isInCheck(int myColor) {
    char myColorKing; 
    int enemyColor; 
    // if im white, my king is K
    if (this -> player == 0) {
        myKing = 'K'; 
        enemyColor = 1; 
    } else {
        myKing = 'k'; 
        theEnemy = 0; 
    }

    // finding where my king is 

    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            Position current_checking{r, c}; 
            Piece *p = getPieceAt(current); 

            if (p != nullptr && p->getSymbol() == myKing) {
                // if my king is the current position (and there has to be a king for it to be a valid setup)
                return isSquareAttacked(current, theEnemy); 
                // if the square is being attacked is true, than true is returned
            }
        }
    }
    return false; 
    // in case there is no king (no king is found), then false gets returned
}

// MAKE SURE ITS COMPATIBLE WITH MOVE CLASS
bool Board::iosLegalMove(Move m, int player) {
    // position already checks it, not sure if this is necessary
    if (!m.prev.isValid() || !m.next.isValid()) {
        return false; 
    }

    // get the piece at the point that we want to move 
    Piece *p = getPieceAt(m.prev); 
    if (p == nullptr || p->getColour() != player) {
        return false; 
    }

    // ---- EVERYTHING ABOVE THIS MIGHT NOT BE REQUIRED (done in the position class already)
    
    // getting the valid moves of the piece and see if our mvoe is one of the valid ones
    vector<Move> validMoves = p->getValidMoves(*this); 

    for (auto i=0; i<validMoves.size(); i++) {
        // Because we didnt define a == operator for Moves, I am comparing it here
        bool sameStart = (validMoves[i].prev.row == m.prev.row &&
                          validMoves[i].prev.col == m.prev.col);
        bool sameEnd = (validMoves[i].next.row == m.next.row &&
                        validMoves[i].next.col == m.next.col);

        if (sameStart && sameEnd) {
            return true; 
        }
    }

    // if the pieces move was not in the valid moves, than something wrong
    return false; 

}

// can just use the isSquareAttacked

bool Board::isInCheck(int playerColour) {
    char myKing; 
    int theEnemy; 

    if (playuer ==0) {
        myKing = 'K'; 
        theEnemy = 1; 
    } else {
        myKing = 'k'; 
        theEnemy = 0; 
    }

    for (int r = 0; r < 8; r++) {
        for (int c = 0; c<8; c++) {
            Position king_current{r, c}; 
            Piece *p = getPieceAt(current); 

            // find my king, and then use the isSquareAttacked funciton to figure out if it is being attacked (and in check)
            if (p != nullptr && p->getSymbol() == myKing) {
                return isSquareAttacked(current, theEnemy); 
            }
        }
    }
    return false; 
}

bool Board::isCheckmate(int player) {
    // needs to be in check, and also stalemate

    if (!isInCheck(player)) {
        return false; // can't be checkmated if not in check 
    }

    // find the king, than check if all the squares around it (that are empty and it ccannot move) 
    // because valid moves only has moves that result in not checkmate, just look and see if the vector is empty, and if it is, then its checkmate

    // go through all the pieces that we have, see if anything gets us out of checkmate, if yes, than big W!
    for (int r=0; r<8; r++) {
        for (int c=0; c<8; c++) {
            Position current{r, c}; 
            Piece *p = getPieceAt(current); 

            if (p != nullptr && p->getColour() == player) {
                vector<Move> validMoves = p-> getValidMoves(*this); 

                // if theres a valid move, than its not checkmate
                if (!validMoves.empty()) {
                    return false; 
                }
            }
        }
    }
    return true; // if no valid moves, then its checkmate 
}   

bool Board::isStalemate(int player) {
    if (isInCheck(player)) {
        return false;
    }

    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            Position current{c, r};
            const Piece *p = getPieceAt(current);

            if (p != nullptr && p->getColour() == player) {
                std::vector<Move> validMoves = p->getValidMoves(*this);
                if (!validMoves.empty()) {
                    return false; // legal move (this includes everything, because we're not in check, doesn't need to get us out of check)
                }
            }
        }
    }
    return true;
}

// because move just says where it ends up. this function has to deal with all the logic for figuring out if a smpecial move happened
bool Board::movePiece(Move m, int turn) {
    // verify legal move (MIGHT ALREADY BE DONE BY POSITION, FIGURE THIS OUT AFTER WILSON IMPLEMENTS IT)
    if (!isLegalMove(m, turn)) {
        return false;
    }

    Piece *p = chessBoard[m.prev.row][m.prev.col].get();
    char sym = p->getSymbol();

    // If a pawn moves diagonally onto an empty square its an en passant
    if ((sym == 'P' || sym == 'p') &&
        m.next.col != m.prev.col &&
        getPieceAt(m.next) == nullptr) {

        Position capturedPawnPos{m.next.col, m.prev.row};
        removePiece(capturedPawnPos);
    }

    // necessary for rooks and kings for castling
    p->setHasMoved(true);
    placePiece(move(chessBoard[m.prev.row][m.prev.col]), m.next);

    // if the King moved 2 columns horizontally, it had to be a castle. Also needs to move the rook in that direction. 
    // we're assuming we're allowed to castle (determine  by some other function)
    if (sym == 'K' || sym == 'k') {
        if (m.next.col - m.prev.col == 2) {
            chessBoard[m.prev.row][7]->setHasMoved(true);
            placePiece(move(chessBoard[m.prev.row][7]), Position{5, m.prev.row});
        } else if (m.prev.col - m.next.col == 2) {
            chessBoard[m.prev.row][0]->setHasMoved(true);
            placePiece(move(chessBoard[m.prev.row][0]), Position{3, m.prev.row});
        }
    }

    // figure out which direction teh pawn is going in, and if it reaches teh end then it promotes
    int promotionRow;
    if (turn == 0) {
        promotionRow = 7;
    } else {
        promotionRow = 0;
    }

    unique_ptr<Piece> promoted;
    if (choice == 'Q' || choice == 'q') {
        promoted = make_unique<Queen>(turn, m.next);
    } else if (choice == 'R' || choice == 'r') {
        promoted = make_unique<Rook>(turn, m.next);
    } else if (choice == 'B' || choice == 'b') {
        promoted = make_unique<Bishop>(turn, m.next);
    } else if (choice == 'N' || choice == 'n') {
        promoted = make_unique<Knight>(turn, m.next);
    } else {
        promoted = make_unique<Queen>(turn, m.next);
    }

    // not sure when this is ever necessary, but set it to false I guess
    promoted->setHasMoved(false);
    placePiece(move(promoted), m.next);

    // if a pawn moved forward twice, then we can only let it en passant immediately afterwards. (set to false afterwards)
    enPassantTarget = Position{-1, -1};

    if ((sym == 'P' || sym == 'p') &&
        // if opponent moved forwards twice, then we can en passant (possibly)
        (m.next.row - m.prev.row == 2 || m.prev.row - m.next.row == 2)) {
        int skippedRow = (m.prev.row + m.next.row) / 2;

        // this target is enpssantable
        enPassantTarget = Position{m.prev.col, skippedRow};
    }
    // forgot what this function even does :| 

    // true the the piece can be mvoed in the manner mentioned in m
    return true;
}

// checks if correct number of kings, pawns are not in teh correct possition (second to seventh row) no checks. and then we're done
bool Board::isValidSetup() {
    // can only be one of each (and cannot be 0)
    int whiteKings = 0; 
    int blackKings = 0; 

    for (int r=0; r<8; r++) {
        for (int c=0; c<8; c++) {
            // find the kings 

            Position current{r, c}; 

            Piece *p = getPieceAt(current); 
            
            // nothing here so nothing to check
            if (p == nullptr) {
                continue;
            }

            char sym = p->getSymbol(); 

            if (sym == 'K') {
                whiteKings++; 
            } 
            if (sym == 'k') {
                blackKings++; 
            }

            // pawns aren't allowed to be in the first or last row (otherwise theyd be promoting)
            if ((r == 0 || r == 7) && (sym == 'P' || sym == 'p')) {
                // crazy logical operator; 
                return false; 
            }
        }
    }

    if (whiteKings != 1 || blackKings != 1) {
        return false; 
        // wrong number of kigns then reject
    }

    if (isInCheck(0) || isInCheck(1)) {
        return false; 
        // if either side is in check, then invalid (I feel like it should be allowed if its their move)
    }

    return true; 
    
}

osteram& operator<<(ostream &out, const Board &b) {
    b.print(out);
    return out;
}
