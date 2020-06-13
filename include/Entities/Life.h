#pragma once

#include "Entity.h"


class Life : public Entity {
public:
    explicit Life(sf::Vector2f position = {0, 0});

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};


