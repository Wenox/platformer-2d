#pragma once

#include "Utility.h"
#include "IConfig.h"


namespace Paused {
    enum class Btn {
        resume,
        options,
        menu,
        SIZE
    };

    constexpr std::initializer_list<Paused::Btn> Buttons = {
        Btn::resume,
        Btn::options,
        Btn::menu
    };

    static_assert(Buttons.size() == toInt(Btn::SIZE));

    struct Config : public IConfig<Btn> {

        constexpr static auto offsetY = 280;

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

