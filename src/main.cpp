#include "Game.h"

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv)
{
   /* sf::RenderWindow window({600, 800}, "Title");

    sf::Keyboard::Key keyCode = sf::Keyboard::Z;

    std::cout << "Key: " << keyCode << std::endl;
    bool wasRebound = false;

    sf::Event e;

    while (true) {
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::KeyPressed) {
                if (!wasRebound) {
                    keyCode = e.key.code;
                    std::cout << "New key: " << keyCode << std::endl;
//                    wasRebound = true;
                }
            }


            if (e.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        window.display();
    }*/



    Game game;
    game.run();

    return 0;
}
