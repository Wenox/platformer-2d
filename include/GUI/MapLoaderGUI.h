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

private:
    Gui::Config<> config;
    Loader::Config loaderConfig;
    int btnIndex{};

    void init() {
        this->buildGUI();
    }

    void buildGUI() override {
        gui.add(tgui::Picture::create("../resources/mapLoader.jpg"));

        for (auto i{0u}; auto btn : Loader::Buttons) {
            const auto& btnName = loaderConfig.widgetsNames[btn];
            widgets.emplace_back(tgui::Button::create(btnName));

            this->loadWidget(widgets[i]);
            ++i;
        }
    }

    void loadWidget(tgui::Widget::Ptr& widget) {
        config.prepare(widget);
        widget->setPosition(gui.getTarget()->getSize().x / 2 - Gui::Config<>::width / 2,
                            240 + 60 * btnIndex);
        btnIndex++;
        gui.add(widget);
    }
};


