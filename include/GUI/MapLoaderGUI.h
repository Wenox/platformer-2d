#pragma once

#include <Window.h>
#include "MapLoaderConfig.h"
#include "GUI.h"
#include <GUI/Core/Config.h>


class MapLoaderGUI : public GUI<> {
public:
    explicit MapLoaderGUI(Window& window) :  GUI{window} {
        this->init();
    }

    Gui::Config<> config;
private:
    Loader::Config loaderConfig;
    int btnIndex{};

    void init() {
        this->buildGUI();
    }

    void buildGUI() override {
        /** background */
        gui.add(tgui::Picture::create("../resources/mapLoader.jpg"));

        /** buttons */
        for (auto i{0u}; auto btn : Loader::Buttons) {
            const auto& btnName = loaderConfig.widgetsNames[btn];
            widgets.emplace_back(tgui::Button::create(btnName));

            this->loadWidget(widgets[i]);
            ++i;
        }

        /** file name editBox */
        auto editBox = tgui::EditBox::create();
        editBox->setSize(config.width, config.height);
        editBox->setTextSize(config.textSize);
        editBox->setPosition(tgui::bindLeft(widgets[to_underlying(Loader::Btn::loadMap)]),
                             tgui::bindBottom(widgets[to_underlying(Loader::Btn::loadMap)]) + 10);
        gui.add(editBox, "editBox");


        /** label editBox */
        auto editBoxLabel = tgui::Label::create("No such file!");
        editBoxLabel->setTextSize(config.textSize - 5);
        editBoxLabel->setPosition(tgui::bindLeft(editBox) - editBoxLabel->getSize().x - 10, tgui::bindTop(editBox) + 12);
        editBoxLabel->getRenderer()->setTextColor(tgui::Color{255, 0, 0});
        editBoxLabel->setVisible(false);
        gui.add(editBoxLabel, "editBoxLabel");

    }

    void loadWidget(tgui::Widget::Ptr& widget) {
        if (btnIndex == 2) ++btnIndex;

        config.prepare(widget);
        widget->setPosition(gui.getTarget()->getSize().x / 2 - Gui::Config<>::width / 2,
                            180 + 60 * btnIndex);
        btnIndex++;
        gui.add(widget);
    }
};


