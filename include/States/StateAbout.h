#pragma once

#include "ResourceManager.h"
#include "StateMachine.h"
#include "StateID.h"


class StateAbout : public State {
public:
    StateAbout(StateMachine& stateMachine, ResourceManager& resources);

    void onCreate() override;

    void processInput() override;
    void update(float) override;
    void draw(Window& window) override;

private:
    StateMachine& stateMachine;
    sf::Sprite aboutInfo;
};


