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
    gui.widgets[to_underlying(Menu::Btn::newGame)]->connect("pressed", [&]() {
        stateMachine = state::loaderID;
    });

    gui.widgets[to_underlying(Menu::Btn::options)]->connect("pressed", [&]() {
        stateMachine = state::optionsID;
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

void StateMenu::onDestroy() {

}

void StateMenu::onActivate() {
    stateMachine.setCameFrom(state::menuID);

    if (mySettings.isSoundEnabled) {
        onHoverBtnSound.setVolume(mySettings.volume);
    } else {
        onHoverBtnSound.setVolume(0.0f);
    }
}

void StateMenu::onDeactivate() {

}

void StateMenu::processInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
        stateMachine = state::initID;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
        stateMachine = state::restartID;
    }
}

void StateMenu::update(float dt) {
    gui.handleEvent(window.getEvent());
}

void StateMenu::draw(Window&) {
    gui.draw();
}