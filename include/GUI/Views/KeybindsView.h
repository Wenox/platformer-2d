#pragma once

#include "View.h"
#include "Config.h"
#include "KeybindsConfig.h"


class KeybindsView : public View<> {
public:
    explicit KeybindsView(Window &window);

private:
    Gui::Config<> config;
    Keybinds::Config optionsConfig;

    void init();
    void buildGUI() override;
    void loadWidget(tgui::Widget::Ptr &widget);
};