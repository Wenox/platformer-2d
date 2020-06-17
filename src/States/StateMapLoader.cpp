#include "StateMapLoader.h"
#include "StateID.h"
#include "StateGame.h"
#include "MapNameValidator.h"

#ifdef _WIN32
    #include <windows.h>
#endif


StateMapLoader::StateMapLoader(StateMachine& stateMachine, Window& window, ResourceManager& resourceManager)
    : stateMachine{stateMachine}
    , window{window}
    , resources{resourceManager}
    , gui{window}
{
    onHoverBtnSound.setBuffer(resourceManager.getSounds()[res::Sound::Bing]);
}


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

    for (auto& widget : gui.widgets) {
        widget->connect("MouseEntered", [&]() {
            onHoverBtnSound.play();
        });
    }

    setMapLoaderButton();
}

void StateMapLoader::printHelp(std::ostream& ost) {
    ost << "It appears you are not Windows user\n";
    ost << "You should manually open the Map Editor in the browser\n";
}

void StateMapLoader::onActivate() {
    gui.setBadMapLabelVisible(false);
    updateHoverSoundVolume();
}

void StateMapLoader::processInput() {
    gui.handleEvent(window.getEvent());
}

void StateMapLoader::update(float) {

}

void StateMapLoader::draw(Window&) {
    gui.draw();
}

void StateMapLoader::setMapLoaderButton() {
    gui.widgets[to_underlying(Loader::Btn::loadMap)]->connect("Pressed", [&]() {
        gui.animateBadMapLabel();
        createGameFrom(gui.getMapName());
    });
}

void StateMapLoader::createGameFrom(std::string_view mapName) {
    if (MapNameValidator mapFile{mapName}; mapFile.isValidFormat() and mapFile.exists()) {

        if (mapFile.isBmp()) mapLoader = std::make_optional<MapLoader<Bmp>>(mapName.data());
        if (mapFile.isTxt()) mapLoader = std::make_optional<MapLoader<Txt>>(mapName.data());

        state::gameID = stateMachine.insert(std::make_shared<StateGame>(stateMachine, resources, mapLoader.value(), window));
        stateMachine = state::gameID;
    }
    else {
        std::clog << "Map file: " << mapName << " does not exist!" << std::endl;
        gui.setBadMapLabelVisible(true);
        gui.clearMapNameBoxWithPrompt();
    }
}

void StateMapLoader::updateHoverSoundVolume() {
    if (mySettings.isSoundEnabled) {
        onHoverBtnSound.setVolume(mySettings.volume);
    } else {
        onHoverBtnSound.setVolume(0.0f);
    }
}