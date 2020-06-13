#pragma once

#include <Encoder/Encoder.h>
#include <Consts.h>
#include "Entity.h"


class Spike : public Entity {
public:
    explicit Spike(Obj::Entity spikeType, sf::Vector2f position);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    Obj::Entity spikeType;

    void setTextureDirection() {
        switch (spikeType) {
            case Obj::Entity::SpikeLeft:
                sprite.rotate(90.0f);
                sprite.move(consts::entityWidth, 0);
                break;
            case Obj::Entity::SpikeRight:
                sprite.rotate(-90.0f);
                sprite.move(0, consts::entityHeight);
                break;
            case Obj::Entity::SpikeTop:
                sprite.rotate(180.0f);
                sprite.move(consts::entityWidth, consts::entityHeight);
                break;
            default: break;
        }
    }
};


