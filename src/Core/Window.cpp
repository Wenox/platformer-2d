#include "Window.h"
#include <SFML/Window/Event.hpp>


Window::Window(const std::string& windowName)
        : window{sf::VideoMode{640, 576}, windowName}
{
    window.setFramerateLimit(3000);

    sf::Image icon;
    if (!icon.loadFromFile("../resources/icon.png"));
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
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
