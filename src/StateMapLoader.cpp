#include "StateMapLoader.h"

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