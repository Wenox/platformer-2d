#include "StateGame.h"

StateGame::StateGame(StateMachine &stateMachine, ResourceManager& resourceManager)
        : stateMachine{stateMachine}, resourceManager{resourceManager}
{
    std::cout << "StateGame::StateGame()" << std::endl;
}

void StateGame::onCreate() {
    std::cout << "MY MANAGER:\n";
    resourceManager.print();
    texture = resourceManager.get("../resources/wizard.png");
    sprite.setTexture(texture);
}

void StateGame::onDestroy() {

}

void StateGame::onActivate() {
    switch (c++) {
        case 0:
            sprite.setTexture(resourceManager.get("../resources/wizard.png"));
            break;
        case 1:
            sprite.setTexture(resourceManager.get("../resources/gray.png"));
            break;
        case 2:
            sprite.setTexture(resourceManager.get("../resources/orange.png"));
            c = 0;
            break;
    }
}

void StateGame::processInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
        stateMachine.switchTo(state::initID);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
        stateMachine.switchTo(state::menuID);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        sprite.move({-5, 0});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        sprite.move({5, 0});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        sprite.move({0, -5});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        sprite.move({0, 5});
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
    window.draw(sprite);
}