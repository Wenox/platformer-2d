#pragma once

#include "Utility.h"
#include "IConfig.h"


namespace Options {
    enum class Btn {
        Jump,
        GoLeft,
        GoRight,
        GoBack,
        SIZE
    };

    constexpr std::initializer_list<Options::Btn> Buttons = {
        Btn::Jump,
        Btn::GoLeft,
        Btn::GoRight,
        Btn::GoBack
    };

    static_assert(Buttons.size() == toInt(Btn::SIZE));


    struct Config : public IConfig<Btn> {

        constexpr static auto offsetY = 250;

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
                    (Options::Btn::Jump, "Jump")
                    (Options::Btn::GoLeft, "Run Left")
                    (Options::Btn::GoRight, "Run Right")
                    (Options::Btn::GoBack, "Go Back");
        }
    };
};


