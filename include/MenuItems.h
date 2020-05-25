#pragma once

#include <map>
#include <iostream>
#include "Utility.h"

namespace Menu {
    enum class Btn {
        newGame,
        loadGame,
        options,
        about,
        exit,
        SIZE
    };

    constexpr std::initializer_list<Btn> Buttons = {
            Btn::newGame,
            Btn::loadGame,
            Btn::options,
            Btn::about,
            Btn::exit
    };

    struct Config {
        std::map<Btn, const char*> buttonNames;

        constexpr void map() {
            mapListOf(buttonNames)
                    (Menu::Btn::newGame, "New Game")
                    (Menu::Btn::loadGame, "Load Game")
                    (Menu::Btn::options, "Options")
                    (Menu::Btn::about, "About")
                    (Menu::Btn::exit, "Exit");
        }

        Config() { this->map(); }
    };
}

