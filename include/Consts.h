#pragma once

namespace consts {
    extern int blocksCountWidth;
    extern int blocksCountHeight;
    constexpr auto entityWidth  = 32;
    constexpr auto entityHeight = 32;

    constexpr auto horizontalVelocity  = 400;
    constexpr auto terminalVelocity    = 20.0;
    constexpr auto gravity             = 10.0f;
    constexpr auto initialJumpVelocity = -60.0;
    constexpr auto hitCeilingVelocity  = 10.0;
}