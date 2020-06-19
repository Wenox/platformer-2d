#pragma once

enum class MovingState {
    movingLeft,
    movingRight,
    standing
};

enum class JumpingState {
    onGround,
    jumping,
    gravity
};