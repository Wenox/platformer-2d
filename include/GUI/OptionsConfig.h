#pragma once

#include "Utility.h"
#include "IConfig.h"


namespace Options {
    enum class Btn {
        Keybinds,
        GoBack,
        SIZE
    };

    constexpr std::initializer_list<Options::Btn> Buttons = {
        Btn::Keybinds,
        Btn::GoBack
    };

    static_assert(Buttons.size() == toInt(Btn::SIZE));


    struct Config : public IConfig<Btn> {

        constexpr static auto offsetY = 350;

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
                    (Options::Btn::Keybinds, "Keybindings")
                    (Options::Btn::GoBack, "Go Back");
        }
    };
};


