#pragma once

#include <SFML/Graphics.hpp>


class MissingFont : public std::exception {
    std::string msg;
public:
    MissingFont(std::string msg = "Missing font") : msg(std::move(msg)) {}

    virtual const char* what() const noexcept override {
        return msg.c_str();
    }
};



class FpsHUD : public sf::Drawable {
public:
    FpsHUD();

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void update(float dt);

private:
    sf::Font font;
    sf::Text fps;

    std::string calcCurrentFps(float dt);
    void setFont();
    void setFps();
};


