#include "StateGame.h"

StateGame::StateGame(StateMachine &stateMachine, ResourceManager<res::Texture, sf::Texture>& textures)
        : stateMachine{stateMachine}, textures{textures}
{
    std::cout << "StateGame::StateGame()" << std::endl;
}

void StateGame::onCreate() {
    texture = textures.get(res::Texture::Wizard);
    sprite.setTexture(texture);
}

void StateGame::onDestroy() {

}

void StateGame::onActivate() {
    switch (c++) {
        case 0:
            sprite.setTexture(textures.get(res::Texture::Wizard));
            break;
        case 1:
            sprite.setTexture(textures.get(res::Texture::Orange));
            break;
        case 2:
            sprite.setTexture(textures.get(res::Texture::Green));
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
}

void StateGame::update(float dt) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        sprite.move({-velocity * dt, 0});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        sprite.move({velocity * dt, 0});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        sprite.move({0, -velocity * dt});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        sprite.move({0, velocity * dt});
    }
}

void StateGame::draw(Window &window) {
    static tgui::Gui gui{window.getWindow()};
    static tgui::Label::Ptr label = tgui::Label::create("State Game");
    label->setTextSize(72);
    gui.add(label);
    gui.draw();



    window.draw(sprite);
}