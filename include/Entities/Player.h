#pragma once

#include "Entity.h"


class Player : public Entity {
private:
    const float velocity = 400.0;

public:
    explicit Player(sf::Vector2f position = {0, 0})
            : Entity{position}
    {}

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        target.draw(sprite, states);
    }

    auto& getVelocity() const {
        return velocity;
    }
};


