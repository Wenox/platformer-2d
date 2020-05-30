#include <TGUI/Gui.hpp>
#include <iostream>
#include "StateID.h"
#include "StateInit.h"


StateInit::StateInit(StateMachine& stateMachine, Window& window)
        : stateMachine{stateMachine},
          window{window}
{
    std::cout << "StateInitializer::StateInitializer()" << std::endl;
}

void StateInit::onCreate()  {

}

void StateInit::onDestroy() {

}

void StateInit::onActivate() {
    std::cout << "State Initializer activated" << std::endl;
}

void StateInit::processInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
        stateMachine.switchTo(state::menuID);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
        stateMachine.switchTo(state::gameID);
    }
}

void StateInit::update(float dt) {

}

void StateInit::draw(Window&) {
    static tgui::Gui gui{window.getWindow()};
    gui.draw();
}