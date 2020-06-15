#pragma once

#include <iostream>
#include <GUI/OptionsGUI.h>
#include <ActionMap.h>
#include <Action.h>
#include <ResourceManager/Resources.h>
#include "State.h"
#include "StateMachine.h"
#include "StateID.h"
#include "ResourceHolder.h"


class StateOptions : public State {
private:

public:
    StateOptions(StateMachine& stateMachine, Window& window, ResourceHolder<res::Texture, sf::Texture>& textures)
    : stateMachine{stateMachine}
    , window{window}
    , gui{window}
    , bg{textures[res::Texture::BgOptions]}
    {}

    void onCreate() override {
        gui.widgets[to_underlying(Options::Btn::Keybinds)]->connect("Pressed", [&]() {
            stateMachine = state::optionsKeysID;
        });
        gui.widgets[to_underlying(Options::Btn::GoBack)]->connect("Pressed", [&]() {
            stateMachine = stateMachine.getCameFrom();
        });


        gui.getGui().get("soundCheckBox")->connect("Clicked", [&]() {
            const auto& slider = gui.getGui().get("soundVolume");
            if (slider->isEnabled()) {
                slider->setEnabled(false);
                slider->setInheritedOpacity(0.5);
            } else {
                slider->setEnabled(true);
                slider->setInheritedOpacity(1.0);
            }
        });
    }

    void onDestroy() override {
    }

    void onActivate() override {
    }

    void processInput() override {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {
            /** save options */
            mySettings.isSoundEnabled = gui.isSoundChecked();
            mySettings.isFpsEnabled   = gui.isFpsChecked();
            mySettings.volume         = gui.getVolume();

            stateMachine = stateMachine.getCameFrom();
        }
    }
    void update(float dt) override {
        gui.handleEvent(window.getEvent());
    }

    void draw(Window& window) override {
        this->window.draw(bg);
        gui.draw();
    }

private:
    StateMachine& stateMachine;
    Window& window;

    OptionsGUI gui;

    sf::Sprite bg;
};


