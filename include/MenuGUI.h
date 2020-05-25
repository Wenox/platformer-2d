#pragma once

#include <iostream>
#include "Window.h"
#include "GraphicItems.h"
#include "GUI.h"
#include "MenuConfig.h"


class MenuGUI : public GUI {
public:
    MenuGUI(Window& window)
    : GUI{window} {
        mapListOf(buttonNames)
                (Menu::Btn::newGame,  "New Game")
                (Menu::Btn::loadGame, "Load Game")
                (Menu::Btn::options,  "Options")
                (Menu::Btn::about,    "About")
                (Menu::Btn::exit, "Exit");


        buildGUI();
    }

private:
    Gui::Config<tgui::Widget::Ptr> config;
    std::map<Menu::Btn, const char*> buttonNames;
    int btnCounter = 0;


    void buildGUI() override {
        gui.add(tgui::Picture::create("../resources/background.jpg"));

        for (auto i{0u}; auto btn : Menu::Buttons) {
            widgets.emplace_back(tgui::Button::create(buttonNames[btn]));
            this->loadWidget(gui, widgets[i]);
            ++i;
        }
    }
public:
    std::vector<tgui::Widget::Ptr> widgets;


private:

    void loadWidget(tgui::Gui& _gui, tgui::Widget::Ptr& widget) {
        config.setWidget(widget);
        widget->setPosition({gui.getTarget()->getSize().x / 2 - config.btnWidth / 2,
                             config.offsetY + gui.getTarget()->getSize().y / 9 * ++btnCounter});
        _gui.add(widget);
    }
};


