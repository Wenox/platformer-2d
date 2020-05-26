#pragma once

#include <iostream>
#include "Window.h"
#include "MenuItems.h"
#include "GUI.h"
#include "Config.h"
#include "Utility.h"


class MenuGUI : public GUI<> {
public:
    explicit MenuGUI(Window& window)
        : GUI{window}
    {
        this->init();
    }

private:
    Gui::Config<> config;
    Menu::Config menuConfig;

    void init() {
        this->buildGUI();
    }

    void buildGUI() override {
        gui.add(tgui::Picture::create("../resources/background.jpg"));

        for (auto i{0u}; auto btn : Menu::Buttons) {
            widgets.emplace_back(tgui::Button::create(menuConfig.buttonNames[btn]));
            this->loadWidget(gui, widgets[i]);
            ++i;
        }
    }

private:
    int btnCounter{0};
    void loadWidget(tgui::Gui& _gui, tgui::Widget::Ptr& widget) {
        config.setWidget(widget);
        widget->setPosition({gui.getTarget()->getSize().x / 2 - config.width / 2,
                             config.offsetY + gui.getTarget()->getSize().y / 9 * ++btnCounter});
        _gui.add(widget);
    }
};


