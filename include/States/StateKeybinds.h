#pragma once

#include <GUI/KeybindsGUI.h>
#include <Action.h>
#include <ActionMap.h>
#include <iostream>
#include "State.h"
#include "StateMachine.h"
#include "StateID.h"


class StateKeybinds : public State {
private:
    Action action;

public:
    StateKeybinds(StateMachine& stateMachine, Window& window)
            : stateMachine{stateMachine}
            , window{window}
            , gui{window}
            , action{Action::NONE}
    {}

    void onCreate() override {
        gui.widgets[to_underlying(OptionsKeys::Btn::Jump)]->connect("Pressed", [&]() {
            action = Action::Jump;
            gui.getGui().get("gamepad")->hideWithEffect(tgui::ShowAnimationType::Scale, sf::milliseconds(150));
            gui.getGui().get("panel")->showWithEffect(tgui::ShowAnimationType::SlideFromLeft, sf::milliseconds(150));
        });
        gui.widgets[to_underlying(OptionsKeys::Btn::GoLeft)]->connect("Pressed", [&]() {
            action = Action::GoLeft;
            gui.getGui().get("gamepad")->hideWithEffect(tgui::ShowAnimationType::Scale, sf::milliseconds(150));
            gui.getGui().get("panel")->showWithEffect(tgui::ShowAnimationType::SlideFromLeft, sf::milliseconds(150));
        });
        gui.widgets[to_underlying(OptionsKeys::Btn::GoRight)]->connect("Pressed", [&]() {
            action = Action::GoRight;
            gui.getGui().get("gamepad")->hideWithEffect(tgui::ShowAnimationType::Scale, sf::milliseconds(150));
            gui.getGui().get("panel")->showWithEffect(tgui::ShowAnimationType::SlideFromLeft, sf::milliseconds(150));
        });

        gui.widgets[to_underlying(OptionsKeys::Btn::GoBack)]->connect("Pressed", [&]() {
            stateMachine = state::optionsID;
        });

        for (auto& widget : gui.widgets) {
            widget->connect("MouseEntered", [&]() {

            });
        }
    }
    void onDestroy() override {

    }

    void onActivate() override {}

    void processInput() override{}
    void update(float dt) override {
        if (window.getEvent().front().type == sf::Event::KeyPressed
            and action != Action::NONE) {

            gui.getGui().get("panel")->hideWithEffect(tgui::ShowAnimationType::SlideToRight, sf::milliseconds(150));
            gui.getGui().get("gamepad")->showWithEffect(tgui::ShowAnimationType::Scale, sf::milliseconds(150));

            if (window.getEvent().front().key.code == sf::Keyboard::Escape) {
                action = Action::NONE;
                return;
            }

            switch (action) {
                case Action::Jump:
                    actionMap.set("Jump", window.getEvent().front().key.code);
                    break;
                case Action::GoLeft:
                    actionMap.set("GoLeft", window.getEvent().front().key.code);
                    break;
                case Action::GoRight:
                    actionMap.set("GoRight", window.getEvent().front().key.code);
                    break;
                default:
                    break;
            }

            action = Action::NONE;

        }

        gui.handleEvent(window.getEvent());
    }
    void draw(Window& window) override {
        gui.draw();
    }

private:
    StateMachine& stateMachine;
    Window& window;

    ActionMap& actionMap = ActionMap::Instance();

    KeybindsGUI gui;
};

