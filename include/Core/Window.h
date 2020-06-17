#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <queue>


class Window {
public:
    explicit Window(const std::string& windowName);

    void update();

    void beginDraw();
    void draw(const sf::Drawable& drawable);
    void endDraw();

    auto& getEvent() {
        return events;
    }

    auto& getWindow() {
        return window;
    }

    void close();
    bool isOpen() const;

    void updateView(const sf::View& view);

private:
    sf::RenderWindow window;
    std::queue<sf::Event> events;

    void setWindowIcon();
};


