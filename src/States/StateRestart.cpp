#include "StateRestart.h"
#include "StateID.h"
#include "Configuration.h"


StateRestart::StateRestart(StateMachine& stateMachine, Window& window, ResourceManager& resourceManager)
        : stateMachine{stateMachine}
        , window{window}
        , gui{window, resourceManager}
{}

void StateRestart::onCreate() {
    gui.widgets[to_underlying(Restart::Btn::PlayAgain)]->connect("pressed", [&]() {
        stateMachine = state::gameID;
    });

    gui.widgets[to_underlying(Restart::Btn::Menu)]->connect("pressed", [&]() {
        stateMachine = state::menuID;
    });
}

void StateRestart::onActivate() {
    config::playerWon ? gui.setGameWonTexture() : gui.setGameLostTexture();
}

void StateRestart::onDeactivate() {
    stateMachine.setPreviousStateID(state::restartID);
}

void StateRestart::processInput() {
    gui.handleEvent(window.getEvent());
}

void StateRestart::draw(Window&) {
    gui.draw();
}