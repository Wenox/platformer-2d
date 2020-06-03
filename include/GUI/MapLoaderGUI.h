#pragma once

#include <Window.h>
#include "MapLoaderConfig.h"
#include "GUI.h"
#include "Config.h"


class MapLoaderGUI : public GUI<> {
public:
    explicit MapLoaderGUI(Window& window);

    Gui::Config<> config;
private:
    Loader::Config loaderConfig;
    int btnIndex{};

    void init();

    void buildGUI() override;

    void loadWidget(tgui::Widget::Ptr& widget);
};


