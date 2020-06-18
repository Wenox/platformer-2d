#pragma once

#include <SFML/Audio/Sound.hpp>
#include "PausedView.h"
#include "ResourceManager.h"
#include "StateMachine.h"
#include "StateID.h"


class StatePaused : public State {
public:
    StatePaused(StateMachine& stateMachine, Window& window, ResourceManager& resources);

    void onCreate() override;

    void onActivate() override;
    void onDeactivate() override;

    void processInput() override;
    void draw(Window&) override;

private:
    StateMachine& stateMachine;
    Window& window;

    sf::View pausedView;

    PausedView gui;

    sf::Sound onHoverBtnSound;
};


