#pragma once

#include <SFML/Audio/Sound.hpp>
#include "OptionsView.h"
#include "ResourceManager.h"
#include "StateMachine.h"


class StateOptions : public State {
public:
    StateOptions(StateMachine& stateMachine, Window& window, ResourceManager& resources);

    void onCreate() override;
    void onActivate() override;

    void processInput() override;
    void draw(Window&) override;

private:
    StateMachine& stateMachine;
    Window& window;

    OptionsView gui;

    std::array<std::reference_wrapper<sf::Texture>, 4> cornersTextures;
    std::array<sf::Sprite, 4> corners;

    sf::Sound onHoverBtnSound;
    void updateHoverSoundVolume();

    void saveOptions();
    void updateSlider();
};


