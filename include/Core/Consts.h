#pragma once

#include <string_view>
#include <SFML/Window/Keyboard.hpp>


namespace consts {
    constexpr static std::string_view mapEditorPath  = "index.html";
    constexpr static std::string_view defaultMapName = "map.bmp";
    constexpr static std::string_view gameMusic      = "../resources/sound/MaquinasOutpost2.ogg";

    constexpr static sf::Keyboard::Key defaultJumpKey     = sf::Keyboard::W;
    constexpr static sf::Keyboard::Key defaultRunLeftKey  = sf::Keyboard::A;
    constexpr static sf::Keyboard::Key defaultRunRightKey = sf::Keyboard::D;

    constexpr static auto initSoundVolume = 30.0f;

    extern int blocksCountWidth;
    extern int blocksCountHeight;
    constexpr static auto entityWidth  = 32;
    constexpr static auto entityHeight = 32;

    constexpr static auto windowWidth  = entityWidth  * 20;
    constexpr static auto windowHeight = entityHeight * 18;
    constexpr static auto maxFps       = 3000; /** Emphasize frame rate independent movement */

    constexpr static auto horizontalVelocity  = 300.0f;
    constexpr static auto initialJumpVelocity = -680.0f;
    constexpr static auto terminalVelocity    = 1000.0f;
    constexpr static auto gravity             = 2000.0f;
    constexpr static auto hitCeilingVelocity  = 10.0f;

    extern bool playerWon;
}