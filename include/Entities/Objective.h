#pragma once

#include "Entity.h"


class Objective : public Entity {
public:
    explicit Objective(sf::Vector2f position)
            : Entity{position}
    {}

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        target.draw(sprite, states);
    }

    /** todo: consider Ro5 everywhere */
};
