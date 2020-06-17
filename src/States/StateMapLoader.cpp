#include "StateMapLoader.h"
#include "StateID.h"
#include "StateGame.h"
#include "FileNameParser.h"

#ifdef _WIN32
    #include <windows.h>
#endif


StateMapLoader::StateMapLoader(StateMachine& stateMachine, Window& window, ResourceManager& resourceManager)
    : stateMachine{stateMachine}
    , window{window}
    , resources{resourceManager}
    , gui{window}
{}


void StateMapLoader::onCreate() {
    gui.widgets[to_underlying(Loader::Btn::openEditor)]->connect("Pressed", [&]() {
#ifdef _WIN32
        ShellExecute(nullptr, "open", consts::mapEditorPath.data(), nullptr, nullptr, SW_SHOWNORMAL);
#elif
        this->printHelp(std::clog);
        stateMachine = state::gameID;
#endif
    });

    gui.widgets[to_underlying(Loader::Btn::goBack)]->connect("Pressed", [&]() {
        stateMachine = state::menuID;
    });

    gui.getGui().get("mapNameBox")->connect("Clicked", [&]() {
        if (gui.isPromptToEnter()) {
            gui.clearMapNameBox();
            gui.setPromptToEnter(false);
        }
    });

    setLoadMapBtn();
}

void StateMapLoader::printHelp(std::ostream& ost) {
    ost << "It appears you are not Windows user\n";
    ost << "You should manually open the Map Editor in the browser\n";
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

void StateMapLoader::setLoadMapBtn() {
    gui.widgets[to_underlying(Loader::Btn::loadMap)]->connect("Pressed", [&]() {
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
            gui.clearMapNameBoxWithPrompt();
        }
    });
}