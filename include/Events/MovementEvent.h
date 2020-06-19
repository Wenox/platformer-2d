/** @file */

#pragma once

#include "Player.h"
#include "Block.h"
#include "PhysicsEvent.h"

/** \class MovementEvent
 *
 *  \ingroup theEvents
 *
 *  \brief MovementEvent class responsible for updating the player movement in an **axis-independent way**.
 *
 *  \note
 *
 *  The idea is that the both axises work independently in terms of MovementEvent, CollisionEvent and Camera. It is much easier to work with when working with one axis at a time.
 *
 *  \note Implements pure virtual methods from base PhysicsEvent class.
 *  */
class MovementEvent : public PhysicsEvent {
public:
    /** \brief Create a MovementEvent instance.
     *
     * @param player - controller
     * @param blocks - entities for the controller to be matched isDetectingGround against */
    MovementEvent(Player& player, std::vector<std::unique_ptr<Entity>>& blocks);

    /** \brief Delete copy operations. */
    MovementEvent(const MovementEvent&) = delete;
    /** \brief Delete copy operations. */
    MovementEvent& operator=(const MovementEvent&) = delete;

    /** \brief Handles horizontal movements on X axis based on MovingState.
     *
     *
     *
     *  Implements PhysicsEvent pure virtual method.
     *
     *  @Example
     */
    void updateAxisX(float dt) override;

    /** \brief Handles all vertical movements on Y axis based on JumpingState.
     *
     *  Player can be in one of three states:
     *    - JumpingStaet::onGround
     *    - JumpingState::jumping
     *    - JumpingState::gravity
     *
     *  \note If the Player is onGround, and he no longer detects the blocks beneath his feet, it means he fell off the edge.
     *  Therefore passive gravity should be turned on by changing the JumpingState to JumpingState::gravity.
     *
     *  Implements PhysicsEvent pure virtual method.
     */
    void updateAxisY(float dt) override;

private:
    Player& player;
    std::vector<std::unique_ptr<Entity>>& blocks;

    const float velX; ///< Binds during MovementEvent construction to minimize getters usage in performance-crucial loop.
};

