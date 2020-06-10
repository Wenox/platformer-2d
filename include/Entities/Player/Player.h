#pragma once

#include <Consts.h>
#include "Entity.h"
#include "PlayerState.h"


class Player : public Entity {
private:
    const float velX = consts::horizontalVelocity;
    float jumpTime = 0.0;
    float velY = consts::initialJumpVelocity;

public:
    explicit Player(sf::Vector2f position = {0, 0})
            : Entity{position}
    {}

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        target.draw(sprite, states);
    }

    float getVelocityX() const {
        return velX;
    }

    float getVelocityY() const {
        return velY;
    }

    void setVelocityY(float newVal) {
        this->velY = newVal;
    }


    void jumpFrame(float dt) {
        jumpTime += dt;
        sprite.move(0, velY * jumpTime);

        if (velY < consts::terminalVelocity) {
            velY += consts::gravity * jumpTime;
        }
    }

    void restartJumpTime() {
        jumpTime = 0.0;
    }

    void landOnGroundUpdate() {
        this->jumpingState = JumpingState::onGround;
        this->setVelocityY(consts::initialJumpVelocity);
        this->restartJumpTime();
    }

    MovingState  movingState{MovingState::standing};
    JumpingState jumpingState{JumpingState::onGround};
};


