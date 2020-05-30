#include <SFML/Audio/Sound.hpp>
#include <Consts.h>
#include "StateGame.h"

StateGame::StateGame(StateMachine &stateMachine, ResourceManager& resources, int blocksNum, std::map<PixelColor, Obj::Entity>& encodedObjects, std::vector<PixelColor>& data)
        : stateMachine{stateMachine}, resources{resources}, blocksNum{blocksNum}, encodedObjects{encodedObjects}, data{data}
{
    std::cout << "StateGame::StateGame()" << std::endl;
    std::cout << "StateGame blocksNum: " << this->blocksNum << std::endl;
}

void StateGame::onCreate() {
    blocks.resize(blocksNum);
    for (auto& block : blocks) {
        block.setTexture(resources.getTextures().get(res::Texture::Block));
    }
    texture = resources.getTextures().get(res::Texture::Wizard);
    sprite.setTexture(texture);

    std::cout << "u\n";
    int u = 0;
    auto j = consts::blocksCountHeight;
    constexpr auto entitiesNum = consts::blocksCountHeight * consts::blocksCountHeight;
    for (int k = 0; k < entitiesNum; k++) {
        if (k % consts::blocksCountWidth == 0) {
            j--;
        }
        int i = k % consts::blocksCountWidth;

        auto curID = encodedObjects.find(data[k]);
        switch (curID->second) {
            case Obj::Entity::Empty:
                break;
            case Obj::Entity::Block:
                blocks[u].setPosition(i * consts::entityWidth, j * consts::entityHeight);
                u++;
                break;
            default:
                break;
        }
    }
}

void StateGame::onDestroy() {

}

void StateGame::onActivate() {
    sprite.setTexture(resources.getTextures()[res::Texture::Wizard]);
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
    window.draw(sprite);
    for (const auto& block : blocks) {
        window.draw(block);
    }
}