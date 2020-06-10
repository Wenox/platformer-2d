#pragma once

#include <Consts.h>
#include "Entity.h"
#include "PlayerState.h"


class Player : public Entity {
private:
    const float velX = consts::horizontalVelocity;
    float jumpTime = 0.0;
    float velY = consts::initialJumpVelocity;
    constexpr static auto detectorRange = 5.0f;

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

    void hitCeilingUpdate() {
        this->setVelocityY(consts::hitCeilingVelocity);
    }

    bool isDetectingGround(const std::vector<std::unique_ptr<Entity>>& blocks) const {
        for (std::size_t i = 0; i < blocks.size(); i++) { /** todo: range-based */
            if (blocks[i]->getGlobalBounds().contains(left(),  bot() + detectorRange)
                ||  blocks[i]->getGlobalBounds().contains(right(), bot() + detectorRange)) {
                return true;
            }
        }
        return false;
    }


    MovingState  movingState{MovingState::standing};
    JumpingState jumpingState{JumpingState::onGround};
};


