#pragma once

#include <TGUI/Color.hpp>
#include "Utility.h"
#include "IConfig.h"


namespace Loader {
    enum class Btn {
        loadMap,
        openEditor,
        goBack,
        SIZE
    };

    constexpr std::initializer_list<Loader::Btn> Buttons = {
        Btn::loadMap,
        Btn::openEditor,
        Btn::goBack
    };

    static_assert(Buttons.size() == toInt(Btn::SIZE));


    struct Config : public IConfig<Btn> {
        tgui::Color mapNameColor = {196, 0, 0};

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
                    (Loader::Btn::loadMap,     "Load map")
                    (Loader::Btn::openEditor,  "Build new map")
                    (Loader::Btn::goBack,"Go back");
        }
    };
};


