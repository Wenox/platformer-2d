#pragma once

#include <string>
#include <SFML/Graphics/RenderWindow.hpp>

class Window {
public:
    explicit Window(const std::string& windowName);

    void update();

    void beginDraw();
    void draw(const sf::Drawable& drawable);
    void endDraw();

    auto& getWindow() const {
        return window;
    }

    bool isOpen() const;
private:

    sf::RenderWindow window;
};


