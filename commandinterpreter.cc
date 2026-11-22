#include <ostream>
#include <sstream>
#include "commandinterpreter.h"

Commandinterpreter::Commandinterpreter() : game{nullptr}, whiteScore{0}, blackScore{0} {}

Commandinterpreter::~Commandinterpreter() {delete game;}

void Commandinterpreter::start(std::istream &in, std::ostream &out) {

}

void Commandinterpreter::beginGame(std::istream &args, std::ostream &out) {

}

void Commandinterpreter::move(std::istream &args, std::ostream &out) {

}

void Commandinterpreter::setup(std::istream &in, std::ostream &out) {

}

void Commandinterpreter::checkEnd() {

}