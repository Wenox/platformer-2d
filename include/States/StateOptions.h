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
    Action action;

public:
    StateOptions(StateMachine& stateMachine, Window& window, Settings& settings, ResourceHolder<res::Texture, sf::Texture>& textures)
    : stateMachine{stateMachine}
    , window{window}
    , settings{settings}
    , gui{window}
    , action{Action::NONE}
    , bg{textures[res::Texture::BgOptions]}
    {}

    void onCreate() override {
        gui.widgets[to_underlying(Options::Btn::Jump)]->connect("Pressed", [&]() {
            action = Action::Jump;
            gui.getGui().get("panel")->showWithEffect(tgui::ShowAnimationType::Scale, sf::milliseconds(150));
        });
        gui.widgets[to_underlying(Options::Btn::GoLeft)]->connect("Pressed", [&]() {
            action = Action::GoLeft;
            gui.getGui().get("panel")->showWithEffect(tgui::ShowAnimationType::Scale, sf::milliseconds(150));
        });
        gui.widgets[to_underlying(Options::Btn::GoRight)]->connect("Pressed", [&]() {
            action = Action::GoRight;
            gui.getGui().get("panel")->showWithEffect(tgui::ShowAnimationType::Scale, sf::milliseconds(150));
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
        if (window.getEvent().front().type == sf::Event::KeyPressed
        and action != Action::NONE) {

            gui.getGui().get("panel")->hideWithEffect(tgui::ShowAnimationType::Scale, sf::milliseconds(150));

            if (window.getEvent().front().key.code == sf::Keyboard::Escape) {
                std::cout << "Escape\n";
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
        this->window.draw(bg);
        gui.draw();
    }

private:
    StateMachine& stateMachine;
    Window& window;
    Settings& settings;

    ActionMap& actionMap = ActionMap::Instance();

    OptionsGUI gui;

    sf::Sprite bg;
};


