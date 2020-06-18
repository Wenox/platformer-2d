#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <queue>


class Window {
public:
    explicit Window(std::string_view windowName);

    void update();

    void beginDraw();
    void draw(const sf::Drawable& drawable);
    void endDraw();

    void close();
    bool isOpen() const;

    void updateView(const sf::View& view);

    std::queue<sf::Event>& getEvent();
    sf::RenderWindow& getWindow();

    unsigned int getWidth()  const noexcept;
    unsigned int getHeight() const noexcept;

private:
    sf::RenderWindow window;
    std::queue<sf::Event> events;

    void setWindowIcon();
};


