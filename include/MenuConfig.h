#pragma once

#include <type_traits>
#include <TGUI/TGUI.hpp>

namespace Gui {
    template <typename Widget>
    struct Config {
        constexpr static auto btnWidth    = 250;
        constexpr static auto btnHeight   = 50;
        constexpr static auto btnTextSize = 24;
        constexpr static auto opacity     = 0.95;
        constexpr static auto offsetY     = 45;

        void setWidget(Widget widget) {
            widget->setSize({btnWidth, btnHeight});
            widget->setInheritedOpacity(opacity);
            widget->setTextSize(btnTextSize);

            if constexpr (std::is_same<Widget, tgui::Button::Ptr>::value) {
                widget->getRenderer()->setBorderColor({209, 153, 48});
                widget->getRenderer()->setBackgroundColor({255, 250, 245});
            }
        }
    };
}