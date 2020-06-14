#include "PausedGUI.h"

void PausedGUI::buildGUI() {
    /** todo: try removing bg from PausedState and use it here instead */
//    gui.add(tgui::Picture::create("../resources/background.jpg"));

    for (auto i{0u}; auto btn : Paused::Buttons) {
        const auto& btnName = menuConfig.widgetsNames[btn];
        widgets.emplace_back(tgui::Button::create(btnName));

        this->loadWidget(widgets[i]);
        ++i;
    }
}

void PausedGUI::loadWidget(tgui::Widget::Ptr& widget) {
    config.prepare(widget);
    widget->setPosition({gui.getTarget()->getSize().x / 2 - Gui::Config<>::width / 2,
                         Paused::Config::offsetY + gui.getTarget()->getSize().y / 9 * ++btnIndex});
    gui.add(widget);
}