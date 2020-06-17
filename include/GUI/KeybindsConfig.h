#pragma once

#include "Utility.h"
#include "IConfig.h"


namespace OptionsKeys {
    enum class Btn {
        Jump,
        RunLeft,
        RunRight,
        GoBack,
        SIZE
    };

    constexpr std::initializer_list<OptionsKeys::Btn> Buttons = {
        Btn::Jump,
        Btn::RunLeft,
        Btn::RunRight,
        Btn::GoBack
    };

    static_assert(Buttons.size() == toInt(Btn::SIZE));

    struct Config : public IConfig<Btn> {

        constexpr static auto offsetY = 288;

        Config() {
            this->init();
        }
#if (__cplusplus == 202002L)
        constexpr
#endif
        void init() {
            this->encode();
        }

#if (__cplusplus == 202002L)
        constexpr
#endif
        void encode() override {
            mapListOf(widgetsNames)
                    (OptionsKeys::Btn::Jump, "Jump")
                    (OptionsKeys::Btn::RunLeft, "Run Left")
                    (OptionsKeys::Btn::RunRight, "Run Right")
                    (OptionsKeys::Btn::GoBack, "Go Back");
        }
    };
};


