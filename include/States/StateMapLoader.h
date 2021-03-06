#pragma once

#include <SFML/Audio/Sound.hpp>
#include "ResourceManager.h"
#include "MapLoaderView.h"
#include "MapLoader.h"
#include "StateMachine.h"


class StateMapLoader : public State {
public:
    StateMapLoader(StateMachine& stateMachine, Window& window, ResourceManager& resourceManager);

    void onCreate() override;
    void onActivate() override;

    void processInput() override;
    void draw(Window&) override;

private:
    StateMachine& stateMachine;
    Window& window;
    ResourceManager& resources;

    MapLoaderView gui;

    std::optional<std::variant<MapLoader<Bmp>, MapLoader<Txt>>> mapLoader;

    sf::Sound onHoverBtnSound;
    void updateHoverSoundVolume();

    void setMapLoaderButton();
    void createGameFrom(std::string_view mapName);

    static void printHelp(std::ostream& ost);
};
