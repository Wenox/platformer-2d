#include "PausedGUI.h"

void PausedGUI::buildGUI() {
    /** todo: try removing bg from PausedState and use it here instead */

    auto panelBorder = tgui::Panel::create({config.width + 22, 205});
    panelBorder->setPosition(184,330);
    panelBorder->getRenderer()->setBackgroundColor(tgui::Color::Magenta);
    panelBorder->setInheritedOpacity(0.25);
    panelBorder->getRenderer()->setBorders({2, 2, 2, 2});
    panelBorder->getRenderer()->setBorderColor(tgui::Color::Black);
    gui.add(panelBorder);

    auto bg = tgui::Picture::create(tgui::Texture{"../resources/PausedBGMain.png"});
    gui.add(bg, "pausedBg");

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