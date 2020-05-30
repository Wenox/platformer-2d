#pragma once

#include "Window.h"
#include "MenuConfig.h"
#include "GUI.h"
#include "Config.h"


class MenuGUI : public GUI<> {
public:
    explicit MenuGUI(Window& window);

private:
    Gui::Config<> config;
    Menu::Config  menuConfig;
    int btnIndex{0};


    void init();
    void buildGUI() override;
    void loadWidget(tgui::Widget::Ptr& widget);
};


