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
    createBackgroundImage();
    createBackgroundPanel();

    for (auto i{0u}; auto btn : Menu::Buttons) {
        const auto &btnName = menuConfig.widgetsNames[btn];
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

void MenuGUI::createBackgroundImage() {
    gui.add(tgui::Picture::create("../resources/background.jpg"));
}

void MenuGUI::createBackgroundPanel() {
    auto panelBorder = tgui::Panel::create({config.width + 22, 330});
    panelBorder->setPosition(184,96);
    panelBorder->getRenderer()->setBackgroundColor(tgui::Color::White);
    panelBorder->setInheritedOpacity(0.35);
    panelBorder->getRenderer()->setBorders({1, 1, 1, 1});
    panelBorder->getRenderer()->setBorderColor(tgui::Color::Black);
    gui.add(panelBorder);
}