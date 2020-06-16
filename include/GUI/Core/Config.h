#pragma once


namespace Gui {
    template <typename Widget = tgui::Widget::Ptr>
    struct Config {
        constexpr static auto width       = 250;
        constexpr static auto height      = 50;
        constexpr static auto textSize    = 24;
        constexpr static auto opacity     = 0.95;


        const static inline tgui::Font font = {"../resources/CascadiaCode.ttf"};


        const tgui::Color borderColor     = {209, 153, 48};
        const tgui::Color backgroundColor = {255, 50, 245};


        void prepare(Widget widget) {
            widget->setSize(tgui::Layout2d{width, height});
            widget->setInheritedOpacity(opacity);
            widget->setTextSize(textSize);
            widget->setInheritedFont(font);

            if constexpr (std::is_same<Widget, tgui::Button::Ptr>::value) {
                widget->getRenderer()->setBorderColor(borderColor);
                widget->getRenderer()->setBackgroundColor(backgroundColor);
            }
        }
    };
}