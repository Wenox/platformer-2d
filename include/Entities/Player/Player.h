#pragma once

#include <Consts.h>
#include "Entity.h"
#include "PlayerState.h"


class Player : public Entity {
private:
    const float velocity = consts::horizontalVelocity;
    float jumpTime = 0.0;
    float velocityY = -60.0;

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

    void jumpFrame(float dt) {
        jumpTime += dt;
        sprite.move(0, velocityY * jumpTime);

        if (velocityY < consts::terminalVelocity) {
            velocityY += consts::gravity * jumpTime;
        }
    }

    MovingState  movingState{MovingState::standing};
    JumpingState jumpingState{JumpingState::onGround};
};


