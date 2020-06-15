#include "Window.h"
#include <SFML/Window/Event.hpp>
#include <iostream>


Window::Window(const std::string& windowName)
    : window{sf::VideoMode{640, 576}, windowName}
{
    window.setFramerateLimit(3000);
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

void Window::close() {
    window.close();
}

bool Window::isOpen() const {
    return window.isOpen();
}
