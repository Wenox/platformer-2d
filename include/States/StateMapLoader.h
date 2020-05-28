#pragma once

#include <GUI/MapLoaderGUI.h>
#include "State.h"
#include "StateMachine.h"


class StateMapLoader : public State {
public:

    StateMapLoader(StateMachine& stateMachine, Window& window)
        : stateMachine{stateMachine}
        , window{window}
        , gui{window}
    {
        std::cout << "StateMapLoader::StateMapLoader()\n";
    }

    void onCreate() override {
        gui.widgets[to_underlying(Loader::Btn::newMap)]->connect("Pressed", [&]() {
            stateMachine = state::gameID;
        });
        gui.widgets[to_underlying(Loader::Btn::loadMap)]->connect("Pressed", [&]() {
            stateMachine = state::menuID;
        });
    }

    void onDestroy() override {

    }

    void processInput() override {

    }

    void update(float) override {
        gui.handleEvent(window.getEvent());
    }

    void draw(Window&) override {
        gui.draw();
    }

private:
    StateMachine& stateMachine;
    Window& window;
    MapLoaderGUI gui;
};


