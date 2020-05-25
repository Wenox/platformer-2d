#pragma once

#include <string>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>


class Window {
public:
    explicit Window(const std::string& windowName);

    void update();

    void beginDraw();
    void draw(const sf::Drawable& drawable);
    void endDraw();

    sf::Event& getEvent() {
        return event;
    }

    auto& getWindow() {
        return window;
    }

    bool isOpen() const;
private:
    sf::RenderWindow window;
    sf::Event event;
};


