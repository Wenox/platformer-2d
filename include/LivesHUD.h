#pragma once

#include "Consts.h"
#include <array>
#include "SFML/Graphics.hpp"
#include "Entity.h"

class Life : public Entity {
private:

public:
    explicit Life(sf::Vector2f position = {0, 0}) : Entity{position} {}

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        target.draw(sprite, states);
    }
};

class Border : public sf::Drawable {
    sf::RectangleShape border;
public:
    explicit Border(const sf::Rect<float>& viewport)
    {
        border.setSize(sf::Vector2f{150, 50});
        border.setOutlineColor(sf::Color::Red);
        border.setOutlineThickness(3);
        border.setFillColor(sf::Color{255, 255, 255, 140});
        border.setPosition(viewport.left + 15, viewport.top + 15);
    }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        target.draw(border, states);
    }
};

class LivesHUD : public sf::Drawable {
private:
    std::array<Life, consts::playerLives> lives;
    int playerLives = consts::playerLives;

    sf::RenderWindow& renderWindow;
    sf::View HUD;

    Border border;
public:
    explicit LivesHUD(sf::RenderWindow& renderWindow, ResourceHolder<res::Texture, sf::Texture>& textures)
    : renderWindow{renderWindow}
    , border{renderWindow.getDefaultView().getViewport()}
    {
        const auto& viewport = renderWindow.getDefaultView().getViewport();
        for (auto i = 0; auto& life : lives) {
            life.getSprite().setTexture(textures[res::Texture::Heart]);
            life.setPosition(viewport.left + 25 + 50 * i++, viewport.top + 25);
        }
    }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        renderWindow.setView(HUD);

        target.draw(border, states);
        for (const auto& life : lives) {
            target.draw(life, states);
        }
    }
};





