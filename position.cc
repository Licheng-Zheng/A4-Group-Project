#include "position.h"

Position::Position(int row, int col) : row{row}, col{col} {}

Position Position::convert(const std::string &s) {
    Position p;
    if (s.length() != 2) return p; //quick length check
    char c = s[0];
    char r = s[1];
    //quick valid input check
    if (c < 'a' || c > 'h' || r < '1' || r > '8') return p;

    //converts letters into index on board by comparing distance
    p.col = c - 'a';
    p.row = '8' - r;
    return p;
}

bool Position::isValid() const { return col >= 0 && col < 8 && row >= 0 && row <8;}

std::string Position::toString() const {
    if (!isValid()) return "burger";
    std::string s;
    
    //convert a position back into letters using the inverse of convert() basically
    char c = 'a' + col;
    char r = '8' - row;
    s += c;
    s += r;
    return s;
}