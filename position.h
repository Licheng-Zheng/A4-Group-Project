#include <string>
#ifndef p
#define p

struct Position {
    int row;
    int col;

    explicit Position(int col = -1, int row = -1);

    //converts moves in letters (e2) into a position
    static Position convert(const std::string &s);

    //converts a position into a move in letters
    std::string toString() const;
    
    bool isValid() const;
};
#endif