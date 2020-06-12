#pragma once

#include <GUI/OptionsGUI.h>
#include "State.h"
#include "StateMachine.h"
#include "StateID.h"


class StateOptions : public State {
public:
    StateOptions(StateMachine& stateMachine, Window& window, Settings& settings)
    : stateMachine{stateMachine}
    , window{window}
    , settings{settings}
    , gui{window}
    {}

    void onCreate() override {
    }
    void onDestroy() override {
    }

    void onActivate() override {
    }

    void processInput() override {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {
            settings.isSoundEnabled = gui.isSoundChecked();
            stateMachine = state::menuID;
        }
    }
    void update(float dt) override {
        gui.handleEvent(window.getEvent());
    }
    void draw(Window& window) override {
        gui.draw();
    }

private:
    StateMachine& stateMachine;
    Window& window;
    Settings& settings;

    OptionsGUI gui;
};


