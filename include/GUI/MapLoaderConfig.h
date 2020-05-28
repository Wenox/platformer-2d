#pragma once

#include "Utility.h"
#include "IConfig.h"


namespace Loader {
    enum class Btn {
        newMap,
        loadMap,
        SIZE
    };

    constexpr std::initializer_list<Loader::Btn> Buttons = {
            Btn::newMap,
            Btn::loadMap
    };

    static_assert(Buttons.size() == toInt(Btn::SIZE));


    struct Config : public IConfig<Btn> {
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
                    (Loader::Btn::newMap, "New map")
                    (Loader::Btn::loadMap, "Load map");
        }
    };
};


