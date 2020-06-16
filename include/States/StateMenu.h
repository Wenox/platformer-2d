#pragma once

#include <GUI/MenuGUI.h>
#include "StateMachine.h"
#include <SFML/Audio.hpp>
#include <Settings.h>
#include "ResourceManager.h"


class StateMenu : public State {
public:
    StateMenu(StateMachine& stateMachine, Window& window, ResourceManager& resourceManager);

    void onCreate() override;
    void onDestroy() override;

    void onActivate() override;
    void onDeactivate() override;

    void processInput() override;
    void update(float dt) override;
    void draw(Window&) override;

private:
    StateMachine& stateMachine;
    Window& window;
    ResourceManager& resources;

    MenuGUI gui;
    sf::Sound onHoverBtnSound;
};


