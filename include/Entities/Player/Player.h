#pragma once

#include <Consts.h>
#include <Entities/Spike.h>
#include <GUI/HUD/LivesHUD.h>
#include <Entities/HeartCollectible.h>
#include "Entity.h"
#include "PlayerState.h"


class Player : public Entity {
private:
    sf::Vector2f startingPosition;
public:
    explicit Player(sf::Vector2f position = {0, 0});

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void jumpFrame(float dt);
    void gravityFrame(float dt);

    void restartJumpTime();

    void landOnGroundUpdate();
    void hitCeilingUpdate();

    bool isDetectingGround(const std::vector<std::unique_ptr<Entity>>& blocks) const;

    bool isIntersecting(const Spike& entity) {
        return this->getGlobalBounds().intersects(entity.getGlobalBounds());
    }

    /** todo: use one interface */
    bool isIntersecting(const HeartCollectible& entity) {
        return this->getGlobalBounds().intersects(entity.getGlobalBounds());
    }

    void kill(LivesHUD& livesHUD) {
        livesHUD.decreaseLife();
        setPosition(startingPosition);
        movingState = MovingState::standing;
        jumpingState = JumpingState::onGround;
    }

    void setStartingPosition() {
        startingPosition = this->sprite.getPosition();
    }

    float getVelocityX() const;
    float getVelocityY() const;

    void setVelocityY(float newVal);

    MovingState  movingState{MovingState::standing};
    JumpingState jumpingState{JumpingState::onGround};

private:
    const float velX = consts::horizontalVelocity;
    float velY = consts::initialJumpVelocity;

    float gravVelY = 0.0;
    float jumpTime = 0.0;

    constexpr static auto detectorRange = 5.0f;

};


