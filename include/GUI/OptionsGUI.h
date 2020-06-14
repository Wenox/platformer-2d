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


        auto jumpBtn = tgui::Button::create();
        jumpBtn->setSize(200, 50);
        jumpBtn->setPosition(250, 300);
        jumpBtn->setText("Set jump key");
        gui.add(jumpBtn, "jumpButton");

        auto promptKey = tgui::Label::create();
        promptKey->setPosition(250, 380);
        promptKey->setVisible(false);
        promptKey->setText("Registering...");
        promptKey->setTextSize(32);
        gui.add(promptKey, "promptKey");

    }

    bool isSoundChecked() const {
        return this->gui.getContainer()->get<tgui::CheckBox>("soundCheckBox")->isChecked();
    }
};


