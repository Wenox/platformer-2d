#pragma once

#include "ResourceManager.h"
#include "StateMachine.h"
#include "StateID.h"


class StateAbout : public State {
public:
    StateAbout(StateMachine& stateMachine, ResourceManager& resources);

    void processInput() override;
    void draw(Window& window) override;

private:
    StateMachine& stateMachine;
    sf::Sprite aboutInfo;
};


