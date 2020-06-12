#pragma once

#include "Entity.h"


class Block : public Entity {
public:
    explicit Block(sf::Vector2f position);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};


