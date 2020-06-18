#include "Window.h"
#include <SFML/Window/Event.hpp>
#include <Core/Consts.h>


Window::Window(std::string_view windowName)
        : window{sf::VideoMode{config::windowWidth, config::windowHeight}, windowName.data()}
{
    window.setFramerateLimit(config::maxFps);
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

std::queue<sf::Event>& Window::getEvent() {
    return events;
}

sf::RenderWindow& Window::getWindow() {
    return window;
}

void Window::setWindowIcon() {
    sf::Image icon;
    if (!icon.loadFromFile(config::programIcon.data())) {
        throw std::runtime_error{"Missing program icon: " + std::string(config::programIcon)};
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

unsigned int Window::getWidth() const noexcept {
    return window.getSize().x;
}

unsigned int Window::getHeight() const noexcept {
    return window.getSize().y;
}
