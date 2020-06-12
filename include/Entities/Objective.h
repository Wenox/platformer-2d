#pragma once

#include "Entity.h"


class Objective : public Entity {
public:
    explicit Objective(sf::Vector2f position = {0, 0});

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    /** todo: consider Ro5 everywhere */
};
