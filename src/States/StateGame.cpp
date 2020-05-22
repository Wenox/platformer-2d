#include "StateGame.h"

StateGame::StateGame(StateMachine &stateMachine)
        : stateMachine{stateMachine}
{
    std::cout << "StateGame::StateGame()" << std::endl;
}

void StateGame::onCreate() {

}

void StateGame::onDestroy() {

}

void StateGame::onActivate() {

}

void StateGame::processInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
        stateMachine.switchTo(state::initID);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
        stateMachine.switchTo(state::menuID);
    }
}

void StateGame::update(float dt) {

}

void StateGame::draw(Window &window) {
    sf::RectangleShape shape({400, 400});
    shape.setFillColor(sf::Color::Red);
    window.draw(shape);


    static tgui::Gui gui{window.getWindow()};
    static tgui::Label::Ptr label = tgui::Label::create("State Game");
    label->setTextSize(72);

    gui.add(label);
    gui.draw();
}