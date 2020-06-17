#include "StateID.h""
#include "Consts.h"
#include "StateRestart.h"


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
    consts::playerWon ? gui.setWonTexture() : gui.setLostTexture();

    stateMachine.setCameFrom(state::restartID);
}

void StateRestart::processInput() {
    gui.handleEvent(window.getEvent());
}

void StateRestart::update(float) {

}

void StateRestart::draw(Window&) {
    gui.draw();
}