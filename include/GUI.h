#pragma once

#include <TGUI/TGUI.hpp>
#include <iostream>
#include "Window.h"
#include "GraphicItems.h"


class GUI {
public:
    GUI(Window& window) {
        gui.setTarget(window.getWindow());
        map_init(buttonNames)
                (Menu::Btn::newGame,  "New Game")
                (Menu::Btn::loadGame, "Load Game")
                (Menu::Btn::options,  "Options")
                (Menu::Btn::about,    "About")
                (Menu::Btn::exit, "Exit");

        gui.add(tgui::Picture::create("../resources/background.jpg"));

        for (auto i{0u}; auto btn : Menu::Buttons) {
            buttons.emplace_back(tgui::Button::create(buttonNames[btn]));
            this->loadButton(gui, buttons[i]);
            ++i;
        }
    }

    void handleEvent(sf::Event e) {
        gui.handleEvent(e);
    }

    void draw() {
        gui.draw();
    }

private:
    std::map<Menu::Btn, const char*> buttonNames;

    int btnCounter = 0;

    constexpr static auto btnWidth    = 250;
    constexpr static auto btnHeight   = 50;
    constexpr static auto btnTextSize = 24;
    constexpr static auto opacity     = 0.95;
    constexpr static auto offsetY     = 45;

    tgui::Gui gui;
public:
    std::vector<tgui::Button::Ptr> buttons;

//    tgui::Button::Ptr newGameBtn  = tgui::Button::create("New Game");
//    tgui::Button::Ptr loadGameBtn = tgui::Button::create("Load Game");
//    tgui::Button::Ptr optionsBtn  = tgui::Button::create("Options");
//    tgui::Button::Ptr aboutBtn    = tgui::Button::create("About");
//    tgui::Button::Ptr exitBtn     = tgui::Button::create("Exit");

private:
    void setButton(tgui::Button::Ptr button) {
        button->setSize({btnWidth, btnHeight});
        button->setPosition({gui.getTarget()->getSize().x / 2 - btnWidth / 2,
                             offsetY + gui.getTarget()->getSize().y / 9 * ++btnCounter});
        button->setInheritedOpacity(opacity);
        button->setTextSize(btnTextSize);

        button->getRenderer()->setBorderColor({209, 153, 48});
        button->getRenderer()->setBackgroundColor({255, 250, 245});
    }

    void loadButton(tgui::Gui& _gui, tgui::Button::Ptr button) {
        setButton(button);
        _gui.add(button);
        std::cout << "Now the size is: " << buttons.size() << std::endl;
    }
};


