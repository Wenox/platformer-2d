#include "Window.h"
#include <SFML/Window/Event.hpp>

Window::Window(const std::string& windowName)
    : window{sf::VideoMode{600, 600}, windowName}
{
    window.setFramerateLimit(60);
}

void Window::update() {
    sf::Event event{};
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }
}

void Window::draw(const sf::Drawable& drawable) {
    window.clear(sf::Color::Cyan);
    window.draw(drawable);
    window.display();
}

bool Window::isOpen() const {
    return window.isOpen();
}
