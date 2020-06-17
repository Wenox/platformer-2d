#include "Settings.h"
#include "StatePaused.h"


StatePaused::StatePaused(StateMachine& stateMachine, Window& window, ResourceManager& resources)
        : stateMachine{stateMachine}
        , window{window}
        , pausedView{{320, 288}, {604, 576}}
        , gui{window}
{
    background.setTexture(resources.getTextures()[res::Texture::BgPaused]);
    onHoverBtnSound.setBuffer(resources.getSounds()[res::Sound::Bing]);
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

    if (mySettings.isSoundEnabled) {
        onHoverBtnSound.setVolume(mySettings.volume);
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
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        stateMachine = state::menuID;
    }
}

void StatePaused::update(float) {

}

void StatePaused::draw(Window&) {
    window.draw(background);
    gui.draw();
}