#pragma once

#include <Window.h>
#include <Settings.h>
#include "GUI.h"
#include "Config.h"
#include "OptionsConfig.h"


class OptionsGUI : public GUI<> {
private:
    Settings settings;

    Gui::Config<> config;
    Options::Config optionsConfig;

    int btnIndex{0};

public:
    explicit OptionsGUI(Window& window)
    : GUI{window}
    {
        this->init();
    }

    void init() {
        this->buildGUI();
    }

    void buildGUI() override;

    void loadWidget(tgui::Widget::Ptr& widget);

        bool isSoundChecked() const {
        return this->gui.getContainer()->get<tgui::CheckBox>("soundCheckBox")->isChecked();
    }
};


