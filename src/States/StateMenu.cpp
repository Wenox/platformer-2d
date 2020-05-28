#include <GUI/MenuConfig.h>
#include "StateMenu.h"



StateMenu::StateMenu(StateMachine& stateMachine, Window& window, ResourceManager& resourceManager)
        : stateMachine{stateMachine},
          window{window},
          gui{window},
          resources{resourceManager}
{
    sound.setBuffer(resources.getSounds().get(res::Sound::Bing));
    std::cout << "StateMenu::StateMenu()\n";
}

void StateMenu::onCreate() {
    for (auto& widget : gui.widgets) {
        widget->connect("MouseEntered", [&]() {
            sound.play();
        });
    }


    gui.widgets[to_underlying(Menu::Btn::newGame)]->connect("pressed", [&]() {
        stateMachine = state::loaderID;
    });

    gui.widgets[to_underlying(Menu::Btn::options)]->connect("pressed", [&]() {
        stateMachine = state::initID;
    });
}

void StateMenu::onDestroy() {

}

void StateMenu::onActivate() {
    std::cout << "State Menu activated" << std::endl;

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