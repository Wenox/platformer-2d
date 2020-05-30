#include "Window.h"
#include <SFML/Window/Event.hpp>

Window::Window(const std::string& windowName)
    : window{sf::VideoMode{608, 608}, windowName}
{
    window.setFramerateLimit(60);
}

void Window::update() {
    sf::Event e{};
    while (window.pollEvent(e)) {
        events.emplace(e);

        if (e.type == sf::Event::Closed) {
            window.close();
        }
    }
}

void Window::beginDraw() {
    window.clear(sf::Color::Cyan);
}

void Window::draw(const sf::Drawable& drawable) {
    window.draw(drawable);
}

void Window::endDraw() {
    window.display();
}

bool Window::isOpen() const {
    return window.isOpen();
}
