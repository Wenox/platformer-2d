#pragma once

#include <iostream>
#include <GUI/OptionsGUI.h>
#include <ActionMap.h>
#include <Action.h>
#include <ResourceManager/Resources.h>
#include "State.h"
#include "StateMachine.h"
#include "StateID.h"
#include "ResourceHolder.h"


class StateOptions : public State {
public:
    StateOptions(StateMachine& stateMachine, Window& window, ResourceHolder<res::Texture, sf::Texture>& textures);

    void onCreate() override;
    void onDeactivate() override;

    void processInput() override;
    void update(float dt) override;
    void draw(Window& window) override;

    void saveOptions();
private:
    StateMachine& stateMachine;
    Window& window;

    OptionsGUI gui;

    std::array<std::reference_wrapper<sf::Texture>, 4> cornersTextures;
    std::array<sf::Sprite, 4> corners;

    void updateSlider();
};


