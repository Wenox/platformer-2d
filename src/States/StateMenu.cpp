#include "StateMenu.h"

StateMenu::StateMenu(StateMachine& stateMachine, Window& window)
        : stateMachine{stateMachine},
          window{window}
{
    std::cout << "StateMenu::StateMenu()\n";
}

void StateMenu::onCreate() {

}

void StateMenu::onDestroy() {

}

void StateMenu::onActivate() {
    std::cout << "State Menu activated" << std::endl;
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

}

void StateMenu::draw(Window& window) {
    sf::RectangleShape shape({400, 400});
    shape.setFillColor(sf::Color::Blue);

    window.draw(shape);

    static tgui::Gui gui{window.getWindow()};
    static tgui::Label::Ptr label = tgui::Label::create("State Menu");
    label->setTextSize(72);

    gui.add(label);
    gui.draw();
}