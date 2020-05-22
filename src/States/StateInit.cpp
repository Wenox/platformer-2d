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

void StateInit::draw(Window& window) {
    sf::RectangleShape shape({400, 400});
    shape.setFillColor(sf::Color::Yellow);
    window.draw(shape);

    static tgui::Gui gui{window.getWindow()};
    static tgui::Label::Ptr label = tgui::Label::create("State Initializer");
    label->setTextSize(72);

    gui.add(label);
    gui.draw();
}