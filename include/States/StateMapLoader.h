#pragma once

#include "FileNameParser.h"
#include "MapLoaderGUI.h"
#include "Game.h"
#include "StateGame.h"
#include "StateID.h"


class StateMapLoader : public State {
public:

    StateMapLoader(Game& game)
        : stateMachine{game.getStateMachine()}
        , window{game.getWindow()}
        , resources{game.getResources()}
        , gui{window}
    {
        std::cout << "StateMapLoader::StateMapLoader()\n";
    }

    void onCreate() override {
        gui.widgets[to_underlying(Loader::Btn::newMap)]->connect("Pressed", [&]() {
            stateMachine = state::gameID;
        });
        gui.widgets[to_underlying(Loader::Btn::loadMap)]->connect("Pressed", [&]() {
            stateMachine = state::menuID;
        });

        setLoadConfirmBtn();
    }

    void onDestroy() override {
        
    }

    void onActivate() override {
        gui.setBadMapLabelVisible(false);
    }

    void processInput() override {

    }

    void update(float) override {
        gui.handleEvent(window.getEvent());

    }

    void draw(Window&) override {
        gui.draw();
    }

private:
    StateMachine& stateMachine;
    Window& window;
    ResourceManager& resources;

    MapLoaderGUI gui;
    std::string mapName{};

    std::optional<std::variant<MapLoader<Bmp>, MapLoader<Txt>>> mapLoader;

    void setLoadConfirmBtn();
};
