#pragma once

#include "Window.h"
#include "MenuConfig.h"
#include "GUI.h"
#include "Config.h"
#include "RestartConfig.h"

#include <iostream>
#include <ResourceManager/ResourceManager.h>

class RestartGUI : public GUI<> {
public:
    explicit RestartGUI(Window& window, ResourceManager& resourceManager) : GUI{window}
            , lostTexture{resourceManager.getTextures()[res::Texture::GameOver]}
            , wonTexture {resourceManager.getTextures()[res::Texture::GameWon]}
            { this->init(); }

private:
    Gui::Config<> config;
    Restart::Config  restartConfig;
    int btnIndex{0};


    const sf::Texture& lostTexture;
    const sf::Texture& wonTexture;

    tgui::Picture::Ptr gameOverImage;


    void init() {
        this->buildGUI();

        this->setWonTexture();
        gameOverImage->setPosition(16, 16);
    }

public:
    void setWonTexture() {
        gameOverImage->getRenderer()->setTexture(wonTexture);
    }

    void setLostTexture() {
        gameOverImage->getRenderer()->setTexture(lostTexture);
    }

private:

    void buildGUI() override {
//        auto bg = tgui::Picture::create(tgui::Texture{"../resources/bindingsBg.jpg"});
        auto bg = tgui::Picture::create(tgui::Texture{"../resources/wonBg.png"});
        gui.add(bg, "bg");


        auto mainPanel = tgui::Panel::create({612, 484});
        mainPanel->setPosition(14,14);
        mainPanel->getRenderer()->setBackgroundColor(tgui::Color::Magenta);
        mainPanel->setInheritedOpacity(0.12);
        mainPanel->getRenderer()->setBorders({4, 4, 4, 4});
        mainPanel->getRenderer()->setBorderColor(tgui::Color::Black);
        gui.add(mainPanel, "mainPanel");

        auto btnPanel = tgui::Panel::create({533, 62});
        btnPanel->setPosition(restartConfig.offsetX - 6,restartConfig.offsetY - 6);
        btnPanel->getRenderer()->setBackgroundColor(tgui::Color::Magenta);
        btnPanel->setInheritedOpacity(0.2);
        btnPanel->getRenderer()->setBorders({2, 2, 2, 2});
        btnPanel->getRenderer()->setBorderColor(tgui::Color::White);
        gui.add(btnPanel, "btnPanel");



        for (auto i{0u}; auto btn : Restart::Buttons) {
            const auto &btnName = restartConfig.widgetsNames[btn];
            widgets.emplace_back(tgui::Button::create(btnName));

            this->loadWidget(widgets[i]);
            ++i;
        }

        gameOverImage = tgui::Picture::create(wonTexture);
        gui.add(gameOverImage, "gameOverImage");

    }

    void loadWidget(tgui::Widget::Ptr& widget) {
        config.prepare(widget);
        auto x = restartConfig.offsetX + (restartConfig.spacing + config.width) * btnIndex;
        widget->setPosition({restartConfig.offsetX + (restartConfig.spacing + config.width) * btnIndex++,
                             restartConfig.offsetY});  /** todo: use Restart::Config without instance of restartConfig */
        gui.add(widget);
    }
};