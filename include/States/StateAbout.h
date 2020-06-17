#pragma once

#include "ResourceManager.h"
#include "StateMachine.h"
#include "StateID.h"


class StateAbout : public State {
public:
    StateAbout(StateMachine& stateMachine, ResourceManager& resources)
    : stateMachine{stateMachine}
    , aboutInfo{resources.getTextures()[res::Texture::AboutInfo]}
    {}

    void onCreate() override {}
    void onDestroy() override {}

    void processInput() override {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            stateMachine.switchTo(state::menuID);
        }
    }

    void draw(Window& window) override {
        window.draw(aboutInfo);
    }

private:
    StateMachine& stateMachine;

    sf::Sprite aboutInfo;
};


