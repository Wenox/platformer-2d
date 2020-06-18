#pragma once

#include "Utility.h"
#include "IConfig.h"


namespace Restart {
    enum class Btn {
        PlayAgain,
        Menu,
        SIZE
    };

    constexpr std::initializer_list<Restart::Btn> Buttons = {
        Btn::PlayAgain,
        Btn::Menu
    };

    static_assert(Buttons.size() == toInt(Btn::SIZE));

    struct Config : public IConfig<Btn> {

        constexpr static auto offsetY = 512;
        constexpr static auto offsetX = 60;
        constexpr static auto spacing = 20;
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

