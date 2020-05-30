#include "MenuGUI.h"


MenuGUI::MenuGUI(Window& window)
        : GUI{window}
{
    this->init();
}

void MenuGUI::init() {
    this->buildGUI();
}

void MenuGUI::buildGUI() {
    gui.add(tgui::Picture::create("../resources/background.jpg"));

    for (auto i{0u}; auto btn : Menu::Buttons) {
        const auto& btnName = menuConfig.widgetsNames[btn];
        widgets.emplace_back(tgui::Button::create(btnName));

        this->loadWidget(widgets[i]);
        ++i;
    }
}

void MenuGUI::loadWidget(tgui::Widget::Ptr& widget) {
    config.prepare(widget);
    widget->setPosition({gui.getTarget()->getSize().x / 2 - Gui::Config<>::width / 2,
                         Menu::Config::offsetY + gui.getTarget()->getSize().y / 9 * ++btnIndex});
    gui.add(widget);
}