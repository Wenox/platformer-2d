#pragma once

#include <string_view>
#include <SFML/Window/Keyboard.hpp>
#include <string>


using std::string_view;
using sf::Keyboard;


namespace config {

    constexpr static Keyboard::Key defaultJumpKey     = Keyboard::W;
    constexpr static Keyboard::Key defaultRunLeftKey  = Keyboard::A;
    constexpr static Keyboard::Key defaultRunRightKey = Keyboard::D;

    constexpr static string_view mapEditorPath        = "index.html";
    constexpr static string_view defaultMapName       = "../resources/Maps/map.bmp";
    constexpr static string_view gameMusic            = "../resources/Music/Background.ogg";

    constexpr static auto defaultSoundVolume          = 30.0f;

    constexpr static string_view widgetsFontName      = "../resources/Fonts/CascadiaCode.ttf";
    constexpr static string_view keybindsFontName     = "../resources/Fonts/NeuropolX.ttf";


    namespace bg {

        constexpr static string_view options          = "../resources/Backgrounds/Options.png";
        constexpr static string_view keybinds         = "../resources/Backgrounds/Keybinds.png";
        constexpr static string_view loader           = "../resources/Backgrounds/Loader.jpg";
        constexpr static string_view menu             = "../resources/Backgrounds/Main_Menu.jpg";
        constexpr static string_view paused           = "../resources/Backgrounds/Paused.png";
        constexpr static string_view restart          = "../resources/Backgrounds/Restart_Game.png";
    }


    constexpr static string_view programIcon          = "../resources/Icons/Program_Icon.png";
    constexpr static string_view jumpIcon             = "../resources/Icons/Jump.png";
    constexpr static string_view runLeftIcon          = "../resources/Icons/Left_Arrow.png";
    constexpr static string_view runRightIcon         = "../resources/Icons/Right_Arrow.png";
    constexpr static string_view largeBgIcon          = "../resources/Icons/Keybinds_Large_Icon.png";


    constexpr static string_view sideBorder           = "../resources/Misc/Options_Side_Border.png";
    constexpr static string_view pausedTextImage      = "../resources/Misc/Game_Paused_Texture.png";
    constexpr static string_view rebindingBg          = "../resources/Misc/Rebinding_Key.png";


    constexpr static auto horizontalVelocity  = 300.0f;
    constexpr static auto initialJumpVelocity = -680.0f;
    constexpr static auto terminalVelocity    = 1000.0f;
    constexpr static auto gravity             = 2000.0f;
    constexpr static auto hitCeilingVelocity  = 10.0f;


    extern int blocksCountWidth;
    extern int blocksCountHeight;
    constexpr static auto entityWidth  = 32;
    constexpr static auto entityHeight = 32;

    constexpr static auto windowWidth  = entityWidth  * 20;
    constexpr static auto windowHeight = entityHeight * 18;
    constexpr static auto maxFps       = 144;

    extern bool playerWon;
}