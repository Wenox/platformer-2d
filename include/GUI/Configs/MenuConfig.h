#pragma once

#include "Utility.h"
#include "IConfig.h"


namespace Menu {
    enum class Btn {
        newGame,
        loadGame,
        options,
        about,
        exit,
        SIZE
    };

    constexpr std::initializer_list<Menu::Btn> Buttons = {
        Btn::newGame,
        Btn::loadGame,
        Btn::options,
        Btn::about,
        Btn::exit
    };

    static_assert(Buttons.size() == toInt(Btn::SIZE));

    struct Config : public IConfig<Btn> {

        constexpr static auto offsetY = 45;

        Config();

#if (__cplusplus == 202002L)
        constexpr
#endif
        void init();

#if (__cplusplus == 202002L)
        constexpr
#endif
        void encode() override;
    };
}

