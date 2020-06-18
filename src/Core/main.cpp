#include "Game.h"


int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv)
{
    try {
        Game game;
        game.run();
    } catch (const std::exception& e) {
        std::cerr << "Caught in main: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
