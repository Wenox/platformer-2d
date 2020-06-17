#pragma once

#include "ResourceManager.h"
#include "MapLoaderGUI.h"
#include "MapLoader.h"
#include "StateMachine.h"


class StateMapLoader : public State {
public:
    StateMapLoader(StateMachine& stateMachine, Window& window, ResourceManager& resourceManager);

    void onCreate() override;
    void onActivate() override;

    void processInput() override;
    void update(float) override;
    void draw(Window&) override;

private:
    StateMachine& stateMachine;
    Window& window;
    ResourceManager& resources;

    MapLoaderGUI gui;

    std::optional<std::variant<MapLoader<Bmp>, MapLoader<Txt>>> mapLoader;

    void setMapLoaderButton();
    void createGameFrom(std::string_view mapName);

    static void printHelp(std::ostream& ost);
};
