#pragma once

#include <SFML/Audio/Sound.hpp>
#include "ResourceManager.h"
#include "KeybindsGUI.h"
#include "Action.h"
#include "ActionMap.h"
#include "StateMachine.h"


class StateKeybinds : public State {
private:
    Action action;

public:
    StateKeybinds(StateMachine& stateMachine, Window& window, ResourceManager& resourceManager);

    void onCreate() override;
    void onActivate() override;

    void processInput() override;
    void update(float dt) override;
    void draw(Window&) override;

private:
    StateMachine& stateMachine;
    Window& window;

    ActionMap& actionMap = ActionMap::Instance();

    KeybindsGUI gui;

    sf::Sound onHoverBtnSound;
    void updateHoverSoundVolume();
};
