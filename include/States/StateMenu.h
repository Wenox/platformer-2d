#pragma once

#include "MenuGUI.h"
#include "StateMachine.h"
#include <SFML/Audio.hpp>
#include <Settings.h>
#include "ResourceManager.h"
#include "MapLoader.h"


class StateMenu : public State {
public:
    StateMenu(StateMachine& stateMachine, Window& window, ResourceManager& resourceManager);

    void onCreate() override;

    void onActivate() override;

    void update(float dt) override;
    void draw(Window&) override;

private:
    StateMachine& stateMachine;
    Window& window;
    ResourceManager& resources;

    MenuGUI gui;
    sf::Sound onHoverBtnSound;

    std::optional<std::variant<MapLoader<Bmp>, MapLoader<Txt>>> mapLoader;
};


