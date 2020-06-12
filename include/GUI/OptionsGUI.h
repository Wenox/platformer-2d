#pragma once

#include <Window.h>
#include <Settings.h>
#include "GUI.h"
#include "Config.h"


class OptionsGUI : public GUI<> {
private:
    Settings settings;
public:
    explicit OptionsGUI(Window& window)
    : GUI{window}
    {
        this->init();
    }

    void init() {
        this->buildGUI();
    }

    void buildGUI() override {
        auto checkBox = tgui::CheckBox::create();
        checkBox->setPosition(100, 200);
        checkBox->setSize(50, 50);
        gui.add(checkBox, "soundCheckBox");
    }

    bool isSoundChecked() const {
        return this->gui.getContainer()->get<tgui::CheckBox>("soundCheckBox")->isChecked();
    }
};


