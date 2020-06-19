#pragma once


/** \enum MovingState
 *
 * \ingroup groupEntities
 *
 * \brief Represents the horizontal MovingState of the player. Player is in one state at a time.
 *
 *
 * */
enum class MovingState {
    movingLeft,
    movingRight,
    standing
};

/** \enum JumpingState
 *
 * \ingroup groupEntities
 *
 * \brief Represents the JumpingState of the player. Player is in one state at a time. */
enum class JumpingState {
    onGround,
    jumping,
    gravity
};