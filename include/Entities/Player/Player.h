/** @file */
#pragma once

#include <Configuration.h>
#include <Entities/Overlay/LivesOverlay.h>
#include "PlayerStates.h"

/** \class Player
 *
 *  \ingroup groupEntities
 *
 *  \brief Controlls the player behaviour.
 *
 *  Player can be in different states:
 *    - \see MovingState
 *    - \see JumpingState
 *
 *
 *  Player texture changes based on running direction.
 *
 * \note A concrete Entity class overriding the draw method.
 *
 * */
class Player : public Entity {
private:
    sf::Vector2f startingPosition; ///< \brief Position player is set to when he needs to be re-spawned.

public:
    /** \brief Constructs the Player.
     * @param position initial position
     * */
    explicit Player(sf::Vector2f position = {0, 0});

    /** \brief Draw method used to render #sprite onto the window.
     * @param target Window for the sprite to be rendered onto.
     * @param states Optional render states
     *
     * Overrides Entity draw method.
     *
     * \note Passing states is optional.
     * */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    /** \brief Performs one tick of a jumping logic.
     *
     * \note Frame-rate independent jump.
     *
     * A jump consists of many consecutive frames. Player has different #jumpVelocity based on the state of jump variables.
     *
     *
     * */
    void jumpFrame(float dt);

    /** \brief Performs one tick of a passive gravity logic.
     *
     * \note Frame-rate independent gravity.
     * A gravity seqeuence consists of many consecutive frames. Player has different #gravVelocity based on the state of jump variables.
     *
     *
     * */
    void gravityFrame(float dt);

    /** \brief Common method for jumpFrame() and gravityFrame(). Updates the velocity based on dt.
     *
     * Terminal velocity is set to infinite velocity growth.
     *
     * @param velocity either #gravVelocity or #jumpVelocity to be updated
     * @param dt time elapsed since previous frame
     *
     * */
    void updateVelocity(float& velocity, float dt) const noexcept;

    /** \brief Update the variables when Player lands on ground. */
    void landOnGroundUpdate();
    /** \brief Update the variables when Player hits the ceiling. */
    void hitCeilingUpdate();
    /** \brief Nullify the #gravVelocity when Player lands on ground. */
    void resetGravVelocity();

    /** Check if Player is standing on the ground.
     *
     * \note Player has ground detectors fixed below his feet.
     * \see #feetDetectorRange */
    bool isDetectingGround(const std::vector<std::unique_ptr<Entity>>& blocks) const;

    /** Check if Player is intersecting other entity.
     *
     * @param entity an arbitrary game entity.
     * @returns Is player intersecting that entity?
     * */
    bool isIntersecting(const Entity& entity) const;

    /** Kills the player.
     *
     * @param lives an overlay of remaining player lives
     *
     * Effectively: one player Life is removed, and Player re-spawns on the #startingPosition.
     *
     * */
    void kill(LivesOverlay& lives);

    /** \brief Sets #startingPosition to wherever the Player currently stands.
     *
     * \warning Do not confuse with setToStartingPosition().
     *
     * */
    void setStartingPosition();
    /** \brief Set Player to his #startingPosition.
     *
     * \warning Do not confuse with setStartingPosition().*/
    void setToStartingPosition();
    /** \brief Retrieve #startingPosition.
     *  @returns sf::Vector2f the player's starting position. */
    sf::Vector2f getStartingPosition() const;

    /** \brief Retrieve horizontal X velocity.
     *
     * @returns float horizontal velocity. */
    float getVelocityX() const;
    /** \brief Retrieve current jump Y velocity.
     * \note Possibly unused.
     * @returns float current jump velocity. */
    [[maybe_unused]] float getJumpVelocity() const;
    /** \brief Retrieve current gravitational Y velocity.
     * \note Possibly unused.
     * @returns float horizontal velocity. */
    [[maybe_unused]] float getGravVelocity() const;
    /** \brief Sets a #jumpVelocity to a new value.
     * @param newVal new value of #jumpVelocity to be set */
    void setJumpVelocity(float newVal);

    MovingState  movingState{MovingState::standing}; ///< \brief Represents the horizontal MovingState of the player. Player is in one state at a time.
    JumpingState jumpingState{JumpingState::onGround}; ///< \brief Represents the vertical JumpingState of the player. Player is in one state at a time.

private:
    const float velocityX = config::horizontalVelocity; ///< \brief Horizontal velocity is a constant.

    const float gravity = config::gravity; ///< Gravity acceleration is a constant.

    /** Two kinds of vertical velocity */
    float jumpVelocity = config::initialJumpVelocity; ///< Used when player himself jumped
    float gravVelocity = 0.0f;                        ///< Used when player is free-falling (e.g. slipped off edge)

    constexpr static auto feetDetectorRange = 5.0f;  ///< Fixed on player's feet to detect the ground.
    float position{};
};


