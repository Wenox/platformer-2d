#pragma once

#include <iostream>
#include <GUI/OptionsGUI.h>
#include <ActionMap.h>
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
        gui.getGui().get("jumpButton")->connect("Pressed", [&]() {
            jumpBtnPressed = true;
            gui.getGui().get("promptKey")->setVisible(true);
        });
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
        if (jumpBtnPressed) {
            if (window.getEvent().front().type == sf::Event::KeyPressed) {
                jumpBtnPressed = false;
                gui.getGui().get("promptKey")->setVisible(false);

                actionMap->set("Jump", window.getEvent().front().key.code);
            }
        }

        gui.handleEvent(window.getEvent());


    }
    void draw(Window& window) override {
        gui.draw();
    }

private:
    StateMachine& stateMachine;
    Window& window;
    Settings& settings;

    ActionMap* actionMap = ActionMap::Instance();

    OptionsGUI gui;

    bool jumpBtnPressed = false;
};


