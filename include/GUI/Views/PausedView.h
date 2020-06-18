#pragma once

#include "View.h"
#include "Config.h"
#include "PausedConfig.h"


class PausedView : public View<> {
public:
    explicit PausedView(Window& window);

private:
    Gui::Config<> config;
    Paused::Config  menuConfig;

    void init();
    void buildGUI() override;
    void loadWidget(tgui::Widget::Ptr& widget);
};


