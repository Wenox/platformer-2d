#pragma once

#include "Window.h"
#include "GUI.h"
#include "GUI/Core/Config.h"
#include "PausedConfig.h"


class PausedGUI : public GUI<> {
public:
    explicit PausedGUI(Window& window) : GUI{window} {
        this->init();
    }

private:
    Gui::Config<> config;
    Paused::Config  menuConfig;
    int btnIndex{0};


    void init() {
        this->buildGUI();
    }
    void buildGUI() override;
    void loadWidget(tgui::Widget::Ptr& widget);
};


