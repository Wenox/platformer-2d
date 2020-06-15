#include "StateID.h"
#include "StateMenu.h"


StateMenu::StateMenu(StateMachine& stateMachine, Window& window, ResourceManager& resourceManager, Settings& settings)
        : stateMachine{stateMachine},
          window{window},
          gui{window},
          resources{resourceManager},
          settings{settings}
{
    onHoverBtnSound.setBuffer(resources.getSounds().get(res::Sound::Bing));
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
    if (settings.isSoundEnabled) {
        onHoverBtnSound.setVolume(100.0f);
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
        stateMachine = state::gameID;
    }
}

void StateMenu::update(float dt) {
    gui.handleEvent(window.getEvent());
}

void StateMenu::draw(Window&) {
    gui.draw();
}