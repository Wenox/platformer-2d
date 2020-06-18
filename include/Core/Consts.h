#pragma once

#include <string_view>
#include <SFML/Window/Keyboard.hpp>

using std::string_view;
using sf::Keyboard;


namespace consts {

    constexpr static string_view mapEditorPath   = "index.html";
    constexpr static string_view defaultMapName  = "map.bmp";
    constexpr static string_view gameMusic       = "../resources/sound/MaquinasOutpost2.ogg";

    namespace bg {

        constexpr static string_view options   = "../resources/test8.png";
        constexpr static string_view keybinds  = "../resources/bindingsBg.png";
        constexpr static string_view rebinding = "../resources/registerBg.png";
        constexpr static string_view loader    = "../resources/mapLoader.jpg";
    }

    constexpr static string_view largeBgIcon  = "../resources/gamepad6.png";
    constexpr static string_view jumpIcon     = "../resources/long-jump2.png";
    constexpr static string_view runLeftIcon  = "../resources/left-arrow2.png";
    constexpr static string_view runRightIcon = "../resources/right-arrow2.png";
    constexpr static string_view sideBorder   = "../resources/side.png";

    constexpr static string_view fontName = "../resources/coolFont.ttf";


    constexpr static Keyboard::Key defaultJumpKey     = Keyboard::W;
    constexpr static Keyboard::Key defaultRunLeftKey  = Keyboard::A;
    constexpr static Keyboard::Key defaultRunRightKey = Keyboard::D;

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