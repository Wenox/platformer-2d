#pragma once

#include "Window.h"
#include "GUI/MenuConfig.h"
#include "GUI/Core/GUI.h"
#include "GUI/Core/Config.h"


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


