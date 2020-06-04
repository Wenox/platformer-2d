#include <Entities/Block.h>
#include "Consts.h"
#include "StateID.h"
#include "StateGame.h"


void StateGame::onCreate() {
    std::visit(overload{
            [&](MapLoader<Bmp>&) { generateWorldFromBmp(); },
            [&](MapLoader<Txt>&) { generateWorldFromTxt(); }
    }, mapLoader);

    std::cout << "Blocks size: " << blocks.size() << std::endl;
    for (auto& block : blocks) {
//        std::cout << "Block: " << block->x() << " " << block->y() << std::endl;

        block->getSprite().setTexture(resources.getTextures().get(queue.front()));
        queue.pop();
    }

    texture = resources.getTextures().get(res::Texture::Wizard);
    sprite.setTexture(texture);
}


void StateGame::onDestroy() {

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

    auto cameraX = sprite.getPosition().x + sprite.getTexture()->getSize().x / 2;
    auto cameraY = sprite.getPosition().y + sprite.getTexture()->getSize().y / 2;

    camera.setCenter(cameraX, cameraY);
    window.getWindow().setView(camera);
}

void StateGame::draw(Window &window) {
    window.draw(sprite);
    for (const auto& block : blocks) {
        window.draw(*block);
    }
}



void StateGame::generateWorldFromBmp() {
    int u = 0;
    auto j = consts::blocksCountHeight;
    const auto entitiesNum = consts::blocksCountHeight * consts::blocksCountWidth;

    auto& mapLoaderRef = std::get<MapLoader<Bmp>>(mapLoader);
    auto& theData =      std::get<BmpReader>(mapLoaderRef.mapReader).getData();
    auto& theEncoded =   std::get<Encoder<PixelColor>>(mapLoaderRef.encoder).encodedObjects;
    blocksNum = mapLoaderRef.getBlocksNum();

    for (int k = 0; k < entitiesNum; k++) {
        if (k % consts::blocksCountWidth == 0) {
            j--;
        }
        int i = k % consts::blocksCountWidth;

        auto curID = theEncoded.find(theData[k]);
        switch (curID->second) {
            case Obj::Entity::Empty:
                break;
            case Obj::Entity::Player:
                sprite.setPosition(i * consts::entityWidth, j * consts::entityHeight);
                break;
            default:
                auto newBlock = std::make_unique<Block>(sf::Vector2f{static_cast<float>(i * consts::entityWidth),
                                                                        static_cast<float>(j * consts::entityHeight)});
                blocks.push_back(std::move(newBlock));
                u++;
                break;
        }
    }
}


void StateGame::generateWorldFromTxt() {
    int u = 0;
    const auto entitiesNum = consts::blocksCountHeight * consts::blocksCountWidth;

    auto& mapLoaderRef = std::get<MapLoader<Txt>>(mapLoader);
    auto& theData =      std::get<TxtReader>(mapLoaderRef.mapReader).getData();
    auto& theEncoded =   std::get<Encoder<int>>(mapLoaderRef.encoder).encodedObjects;

    blocksNum = mapLoaderRef.getBlocksNum();

    for (int k = 0, j = -1; k < entitiesNum; k++) {
        int i = k % consts::blocksCountWidth;
        if (k % consts::blocksCountWidth == 0) {
            j++;
        }
        auto curID = theEncoded.find(theData[k]);
        switch (curID->second) {
            case Obj::Entity::Empty:
                break;
            case Obj::Entity::Player:
                sprite.setPosition(i * consts::entityWidth, j * consts::entityHeight);
                break;
            default:
                auto newBlock = std::make_unique<Block>(sf::Vector2f{static_cast<float>(i * consts::entityWidth),
                                                                     static_cast<float>(j * consts::entityHeight)});
                blocks.push_back(std::move(newBlock));
                u++;
                break;
        }
    }
}


