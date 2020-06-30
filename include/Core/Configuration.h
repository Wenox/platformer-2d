#pragma once

#include <string_view>
#include <SFML/Window/Keyboard.hpp>
#include <string>


using std::string_view;
using sf::Keyboard;


namespace config {

    static constexpr Keyboard::Key defaultJumpKey     = Keyboard::W;
    static constexpr Keyboard::Key defaultRunLeftKey  = Keyboard::A;
    static constexpr Keyboard::Key defaultRunRightKey = Keyboard::D;

    static constexpr string_view mapEditorPath        = "index.html";
    static           std::string defaultMapDir        = "../resources/Maps/";
    static           std::string defaultMapName       = defaultMapDir + "map.bmp";
    static constexpr string_view gameMusic            = "../resources/Music/Background.ogg";

    static constexpr auto defaultSoundVolume          = 30.0f;

    static constexpr string_view widgetsFontName      = "../resources/Fonts/CascadiaCode.ttf";
    static constexpr string_view keybindsFontName     = "../resources/Fonts/NeuropolX.ttf";


    namespace bg {

        static constexpr string_view options          = "../resources/Backgrounds/Options.png";
        static constexpr string_view keybinds         = "../resources/Backgrounds/Keybinds.png";
        static constexpr string_view loader           = "../resources/Backgrounds/Loader.jpg";
        static constexpr string_view menu             = "../resources/Backgrounds/Main_Menu.jpg";
        static constexpr string_view paused           = "../resources/Backgrounds/Paused.png";
        static constexpr string_view restart          = "../resources/Backgrounds/Restart_Game.png";
    }


    static constexpr string_view programIcon          = "../resources/Icons/Program_Icon.png";
    static constexpr string_view jumpIcon             = "../resources/Icons/Jump.png";
    static constexpr string_view runLeftIcon          = "../resources/Icons/Left_Arrow.png";
    static constexpr string_view runRightIcon         = "../resources/Icons/Right_Arrow.png";
    static constexpr string_view largeBgIcon          = "../resources/Icons/Keybinds_Large_Icon.png";


    static constexpr string_view sideBorder           = "../resources/Misc/Options_Side_Border.png";
    static constexpr string_view pausedTextImage      = "../resources/Misc/Game_Paused_Texture.png";
    static constexpr string_view rebindingBg          = "../resources/Misc/Rebinding_Key.png";


    static constexpr auto horizontalVelocity  = 300.0f;
    static constexpr auto initialJumpVelocity = -680.0f;
    static constexpr auto terminalVelocity    = 1000.0f;
    static constexpr auto gravity             = 2000.0f;
    static constexpr auto hitCeilingVelocity  = 10.0f;


    extern int blocksCountWidth;
    extern int blocksCountHeight;
    constexpr static auto entityWidth  = 32;
    constexpr static auto entityHeight = 32;

    constexpr static auto windowWidth  = entityWidth  * 20;
    constexpr static auto windowHeight = entityHeight * 18;
    constexpr static auto maxFps       = 144;

    extern bool playerWon;
}