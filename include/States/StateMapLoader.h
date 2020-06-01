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

        setGui();

        gui.widgets[to_underlying(Loader::Btn::loadConfirm)]->connect("Pressed", [&]() {
            if (FileNameParser mapFile{mapName}; mapFile.isNameCorrect()) {
                if (mapFile.isBmp()) mapLoader = std::make_optional<MapLoader<Bmp>>(mapName);
                if (mapFile.isTxt()) mapLoader = std::make_optional<MapLoader<Txt>>(mapName);

                state::gameID = stateMachine.insert(std::make_shared<StateGame>(stateMachine, resources, mapLoader.value(), window));
                stateMachine = state::gameID;
            }
            else {
                std::cerr << "Name: " << mapName << " is not a valid file name!\n";
                ///< clear mapName edit box, prompt user to enter correct map's file name
            }
        });
    }

    void onDestroy() override {

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

    void setGui();
};
