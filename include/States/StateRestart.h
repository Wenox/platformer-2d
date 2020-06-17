#pragma once

#include <Consts.h>
#include "ResourceManager.h"
#include "StateMachine.h"
#include "StateID.h"
#include "RestartGUI.h"



class StateRestart : public State {
public:
    StateRestart(StateMachine& stateMachine, Window& window, ResourceManager& resourceManager)
    : stateMachine{stateMachine}
    , window{window}
    , gui{window, resourceManager}
    {}

    void onCreate() override {
        gui.widgets[to_underlying(Restart::Btn::PlayAgain)]->connect("pressed", [&]() {
            stateMachine = state::gameID;
        });

        gui.widgets[to_underlying(Restart::Btn::Menu)]->connect("pressed", [&]() {
            stateMachine = state::menuID;
        });
    }

    void onActivate() override {
        consts::playerWon ? gui.setWonTexture() : gui.setLostTexture();

        stateMachine.setCameFrom(state::restartID);
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

    RestartGUI gui;
};