#pragma once

#include "View.h"
#include "Config.h"
#include "MenuConfig.h"


class MenuView : public View<> {
public:
    explicit MenuView(Window& window);

private:
    Gui::Config<> config;
    Menu::Config  menuConfig;

    void init();
    void buildGUI() override;
    void loadWidget(tgui::Widget::Ptr& widget);

    void createBackgroundImage();
    void createBackgroundPanel();
};


