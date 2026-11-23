#include "player.h"

// init player colour
Player::Player(int colour): colour{colour} {}

// getter for colour
int Player::getColour() const {
    return colour;
}

