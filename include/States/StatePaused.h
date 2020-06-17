#pragma once

#include <SFML/Audio/Sound.hpp>
#include "PausedGUI.h"
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
    void update(float) override;
    void draw(Window&) override;

private:
    StateMachine& stateMachine;
    Window& window;

    sf::Sprite background;
    sf::View pausedView;

    PausedGUI gui;

    sf::Sound onHoverBtnSound;
};


