#pragma once

#include <Consts.h>
#include <Entities/Overlay/LivesOverlay.h>
#include "PlayerStates.h"


class Player : public Entity {
private:
    sf::Vector2f startingPosition;

public:
    explicit Player(sf::Vector2f position = {0, 0});

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void jumpFrame(float dt);
    void gravityFrame(float dt);
    void updateVelocity(float& velocity, float dt) const noexcept;

    void landOnGroundUpdate();
    void hitCeilingUpdate();
    void resetGravVelocity();

    bool isDetectingGround(const std::vector<std::unique_ptr<Entity>>& blocks) const;
    bool isIntersecting(const Entity& entity) const;

    void kill(LivesOverlay& lives);

    void setStartingPosition();
    void setToStartingPosition();
    sf::Vector2f getStartingPosition() const;

    float getVelocityX() const;
    [[maybe_unused]] float getJumpVelocity() const;
    [[maybe_unused]] float getGravVelocity() const;
    void setJumpVelocity(float newVal);

    MovingState  movingState{MovingState::standing};
    JumpingState jumpingState{JumpingState::onGround};

private:
    const float velocityX = config::horizontalVelocity;

    float gravity = config::gravity;

    /** Two kinds of vertical velocity */
    float jumpVelocity = config::initialJumpVelocity; ///< used when player himself jumped
    float gravVelocity = 0.0f;                        ///< used when player is free-falling (e.g. slipped off edge)

    constexpr static auto feetDetectorRange = 5.0f;
    float position{};
};


