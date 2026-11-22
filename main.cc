#include <iostream>
#include "commandinterpreter.h"

int main() {
    Commandinterpreter c;
    c.start(std::cin, std::cout);
}