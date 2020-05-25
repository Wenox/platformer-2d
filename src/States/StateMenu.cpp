#include "StateMenu.h"

StateMenu::StateMenu(StateMachine& stateMachine, Window& window)
        : stateMachine{stateMachine},
          window{window},
          gui{window}
{
    std::cout << "StateMenu::StateMenu()\n";
}

void StateMenu::onCreate() {
    gui.newGameBtn->connect("pressed", [&]() {
        stateMachine = state::gameID;
    });

    gui.loadGameBtn->connect("pressed", [&]() {
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