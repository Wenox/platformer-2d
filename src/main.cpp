#include "Game.h"
#include <variant>
#include <iostream>
#include <string>
#include <Encoder/BmpReader.h>


int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv)
{
    Game game;
    game.run();

    return 0;
}