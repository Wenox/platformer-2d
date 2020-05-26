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

    template <typename E>
    struct IConfig {

/** C++20: constexpr virtual */
#if (__cplusplus == 202002L)
        constexpr
#endif
        virtual void map() = 0;
        std::map<E, const char*> buttonNames;
    };

    struct Config : public IConfig<Btn> {
        Config() {
            this->init();
        }

#if (__cplusplus == 202002L)
        constexpr
#endif
        void init() {
            this->map();
        }

#if (__cplusplus == 202002L)
        constexpr
#endif
        void map() override {
            mapListOf(buttonNames)
                    (Menu::Btn::newGame, "New Game")
                    (Menu::Btn::loadGame, "Load Game")
                    (Menu::Btn::options, "Options")
                    (Menu::Btn::about, "About")
                    (Menu::Btn::exit, "Exit");
        }
    };
}

