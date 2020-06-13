#pragma once

#include "MapLoaderGUI.h"
#include "Game.h"
#include "MapLoader.h"


class StateMapLoader : public State {
public:

    explicit StateMapLoader(Game& game);

    void onCreate() override;
    void onDestroy() override;

    void onActivate() override;

    void update(float) override;
    void draw(Window&) override;

private:
    StateMachine& stateMachine;
    Window& window;
    ResourceManager& resources;

    MapLoaderGUI gui;
    std::string mapName{};

    std::optional<std::variant<MapLoader<Bmp>, MapLoader<Txt>>> mapLoader;

    void setLoadConfirmBtn();
};
