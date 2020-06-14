#pragma once

#include "Utility.h"
#include "IConfig.h"


namespace Options {
    enum class Btn {
        Jump,
        GoLeft,
        GoRight,
        SIZE
    };

    constexpr std::initializer_list<Options::Btn> Buttons = {
        Btn::Jump,
        Btn::GoLeft,
        Btn::GoRight
    };

    static_assert(Buttons.size() == toInt(Btn::SIZE));


    struct Config : public IConfig<Btn> {

        constexpr static auto offsetY = 300;

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
                    (Options::Btn::GoLeft, "GoLeft")
                    (Options::Btn::GoRight, "GoRight");
        }
    };
};


