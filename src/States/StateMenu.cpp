#include "Settings.h""
#include "MapNameValidator.h"
#include "StateID.h"
#include "StateMenu.h"


StateMenu::StateMenu(StateMachine& stateMachine, Window& window, ResourceManager& resourceManager)
        : stateMachine{stateMachine},
          window{window},
          resources{resourceManager},
          gui{window}
{
    onHoverBtnSound.setBuffer(resources.getSounds()[res::Sound::Bing]);
}

void StateMenu::onCreate() {
    gui.widgets[to_underlying(Menu::Btn::loadGame)]->connect("pressed", [&]() {
        stateMachine = state::loaderID;
    });

    gui.widgets[to_underlying(Menu::Btn::newGame)]->connect("pressed", [&]() {
        if (MapNameValidator mapFile{consts::defaultMapName.data()}; mapFile.isValidFormat() and mapFile.exists()) {
            if (mapFile.isBmp()) mapLoader = std::make_optional<MapLoader<Bmp>>(consts::defaultMapName.data());
            if (mapFile.isTxt()) mapLoader = std::make_optional<MapLoader<Txt>>(consts::defaultMapName.data());

            state::gameID = stateMachine.insert(
                    std::make_shared<StateGame>(stateMachine, window, resources, mapLoader.value()));
            stateMachine.switchTo(state::gameID);
        } else {
            throw std::runtime_error{"Such default map file does not exist: " + std::string(consts::defaultMapName.data())};
        }
    });

    gui.widgets[to_underlying(Menu::Btn::options)]->connect("pressed", [&]() {
        stateMachine = state::optionsID;
    });

    gui.widgets[to_underlying(Menu::Btn::about)]->connect("pressed", [&]() {
        stateMachine = state::aboutID;
    });

    gui.widgets[to_underlying(Menu::Btn::exit)]->connect("pressed", [&]() {
        window.close();
    });

    for (auto& widget : gui.widgets) {
        widget->connect("MouseEntered", [&]() {
            onHoverBtnSound.play();
        });
    }
}

void StateMenu::onActivate() {
    updateHoverSoundVolume();
}

void StateMenu::onDeactivate() {
    stateMachine.setPreviousStateID(state::menuID);
}

void StateMenu::processInput() {
    gui.handleEvent(window.getEvent());
}

void StateMenu::update(float) {

}

void StateMenu::draw(Window&) {
    gui.draw();
}

void StateMenu::updateHoverSoundVolume() {
    if (mySettings.isSoundEnabled) {
        onHoverBtnSound.setVolume(mySettings.volume);
    } else {
        onHoverBtnSound.setVolume(0.0f);
    }
}