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

osteram& operator<<(ostream &out, const Board &b) {
    b.print(out);
    return out;
}
