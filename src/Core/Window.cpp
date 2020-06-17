#include "Window.h"
#include <SFML/Window/Event.hpp>
#include <Core/Consts.h>


Window::Window(const std::string& windowName)
        : window{sf::VideoMode{consts::windowWidth, consts::windowHeight}, windowName}
{
    window.setFramerateLimit(consts::maxFps);
    setWindowIcon();
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

void Window::updateView(const sf::View& view) {
    window.setView(view);
}
void Window::setWindowIcon() {
    sf::Image icon;
    if (!icon.loadFromFile("../resources/icon.png")) {
        throw std::runtime_error{"Missing icon.png"};
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}
