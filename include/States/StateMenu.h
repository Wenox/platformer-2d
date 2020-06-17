#pragma once

#include "StateGame.h""
#include "MenuGUI.h"


class StateMenu : public State {
public:
    StateMenu(StateMachine& stateMachine, Window& window, ResourceManager& resourceManager);

    void onCreate() override;
    void onActivate() override;
    void onDeactivate() override;

    void processInput() override;
    void update(float) override;
    void draw(Window&) override;

private:
    StateMachine& stateMachine;
    Window& window;
    ResourceManager& resources;

    MenuGUI gui;
    sf::Sound onHoverBtnSound;

    std::optional<std::variant<MapLoader<Bmp>, MapLoader<Txt>>> mapLoader;

    void updateHoverSoundVolume();
};


