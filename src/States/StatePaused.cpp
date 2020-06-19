/** @file */
#include "Settings.h"
#include "StatePaused.h"


StatePaused::StatePaused(StateMachine& stateMachine, Window& window, ResourceManager& resources)
        : stateMachine{stateMachine}
        , window{window}
        , pausedView{{320, 288}, {604, 576}}
        , gui{window}
{
    onHoverBtnSound.setBuffer(resources.getSounds()[res::Sound::BtnHover]);
}

void StatePaused::onCreate() {
    gui.widgets[to_underlying(Paused::Btn::resume)]->connect("pressed", [&]() {
        stateMachine = state::gameID;
    });

    gui.widgets[to_underlying(Paused::Btn::options)]->connect("pressed", [&]() {
        stateMachine = state::optionsID;
    });

    gui.widgets[to_underlying(Paused::Btn::menu)]->connect("pressed", [&]() {
        stateMachine.erase(state::gameID);
        stateMachine = state::menuID;
    });

    for (auto& widget : gui.widgets) {
        widget->connect("MouseEntered", [&]() {
            onHoverBtnSound.play();
        });
    }
}

void StatePaused::onActivate() {
    window.getWindow().setView(pausedView);

    if (audioConfig.isSoundEnabled) {
        onHoverBtnSound.setVolume(audioConfig.volume);
    } else {
        onHoverBtnSound.setVolume(0.0f);
    }
}

void StatePaused::onDeactivate() {
    stateMachine.setPreviousStateID(state::pausedID);
}

void StatePaused::processInput() {
    gui.handleEvent(window.getEvent());

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        stateMachine = state::gameID;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) {
        stateMachine = state::menuID;
    }
}

void StatePaused::draw(Window&) {
    gui.draw();
}