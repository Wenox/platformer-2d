#pragma once

#include "Entity.h"


class Block : public Entity {
public:
    Block(sf::Vector2f position)
        : Entity{position}
    {}

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        target.draw(sprite, states);
    }
};


