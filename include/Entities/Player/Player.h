#pragma once

#include <Consts.h>
#include "Entity.h"
#include "PlayerState.h"


class Player : public Entity {
private:
    const float velocity = consts::horizontalVelocity;

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

    MovingState  movingState{MovingState::standing};
    JumpingState jumpingState{JumpingState::onGround};
};


