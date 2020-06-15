#pragma once

#include <string_view>


namespace consts {
    constexpr std::string_view mapEditorPath = "index.html";

    constexpr auto initSoundVolume = 80.0f;

    extern int blocksCountWidth;
    extern int blocksCountHeight;
    constexpr auto entityWidth  = 32;
    constexpr auto entityHeight = 32;


    constexpr auto horizontalVelocity  = 400;
    constexpr auto terminalVelocity    = 3.75;
    constexpr auto gravity             = 1.40f;
    constexpr auto initialJumpVelocity = -18.5f;
    constexpr auto hitCeilingVelocity  = 10.0;
}