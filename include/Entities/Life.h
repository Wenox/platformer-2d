#pragma once

#include "Entity.h"


class Life : public Entity {
    bool lifeAvailable = true;

    sf::Texture* aliveTexture{};
    sf::Texture* deadTexture{};
public:
    explicit Life(sf::Vector2f position = {0, 0});

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    bool isAvailable() const { return lifeAvailable; }

    void kill() {
        lifeAvailable = false;
        this->getSprite().setTexture(*deadTexture);
    }

    void revive() {
        lifeAvailable = true;
        this->getSprite().setTexture(*aliveTexture);
    }

    void storeAliveTexture(sf::Texture& texture) {
        aliveTexture = &texture;
    }

    void storeDeadTexture(sf::Texture& texture) {
        deadTexture = &texture;
    }

    sf::Texture& getAliveTexture() const {
        return *aliveTexture;
    }
    sf::Texture& getDeadTexture() const {
        return *deadTexture;
    }

};


