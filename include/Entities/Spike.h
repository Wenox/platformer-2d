#pragma once

#include <Encoder/Encoder.h>
#include <Consts.h>
#include "Entity.h"


class Spike : public Entity {
public:
    explicit Spike(Obj::Entity spikeType, sf::Vector2f position);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    Obj::Entity spikeType;

    void setTextureDirection();
};


