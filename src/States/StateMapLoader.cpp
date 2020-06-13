#include "StateMapLoader.h"
#include "StateID.h"
#include "StateGame.h"
#include "FileNameParser.h"


StateMapLoader::StateMapLoader(Game& game)
    : stateMachine{game.getStateMachine()}
    , window{game.getWindow()}
    , resources{game.getResources()}
    , gui{window}
{}

void StateMapLoader::onCreate() {
    gui.widgets[to_underlying(Loader::Btn::newMap)]->connect("Pressed", [&]() {
        stateMachine = state::gameID;
    });
    gui.widgets[to_underlying(Loader::Btn::loadMap)]->connect("Pressed", [&]() {
        stateMachine = state::menuID;
    });

    setLoadConfirmBtn();
}

void StateMapLoader::onDestroy() {

}

void StateMapLoader::onActivate() {
    gui.setBadMapLabelVisible(false);
}

void StateMapLoader::update(float) {
    gui.handleEvent(window.getEvent());
}

void StateMapLoader::draw(Window&) {
    gui.draw();
}

void StateMapLoader::setLoadConfirmBtn() {
    gui.widgets[to_underlying(Loader::Btn::loadConfirm)]->connect("Pressed", [&]() {
        mapName = gui.getMapName();
        gui.animateBadMapLabel();

        if (FileNameParser mapFile{mapName}; mapFile.isValidFormat() and mapFile.exists()) {
            if (mapFile.isBmp()) mapLoader = std::make_optional<MapLoader<Bmp>>(mapName);
            if (mapFile.isTxt()) mapLoader = std::make_optional<MapLoader<Txt>>(mapName);

            state::gameID = stateMachine.insert(std::make_shared<StateGame>(stateMachine, resources, mapLoader.value(), window));
            stateMachine = state::gameID;
        }
        else {
            std::cerr << "Map file: " << mapName << " does not exist!\n";
            gui.setBadMapLabelVisible(true);
            gui.clearMapNameBox();
        }
    });
}