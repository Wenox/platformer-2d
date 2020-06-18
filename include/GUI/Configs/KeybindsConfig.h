#pragma once

#include "Utility.h"
#include "IConfig.h"


namespace Keybinds {
    enum class Btn {
        Jump,
        RunLeft,
        RunRight,
        GoBack,
        SIZE
    };

    constexpr std::initializer_list<Keybinds::Btn> Buttons = {
        Btn::Jump,
        Btn::RunLeft,
        Btn::RunRight,
        Btn::GoBack
    };

    static_assert(Buttons.size() == toInt(Btn::SIZE));

    struct Config : public IConfig<Btn> {

        constexpr static auto offsetY = 288;

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
};


