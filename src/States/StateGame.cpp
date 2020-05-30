#include "Consts.h"
#include "StateID.h"
#include "StateGame.h"


void StateGame::onCreate() {
    std::visit(overload{
            [&](MapLoader<Bmp>&) { generateWorldFromBmp(); },
            [&](MapLoader<Txt>&) { generateWorldFromTxt(); }
    }, mapLoader);

    for (auto& block : blocks) {
        block.setTexture(resources.getTextures().get(res::Texture::Block));
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
}

void StateGame::draw(Window &window) {
    window.draw(sprite);
    for (const auto& block : blocks) {
        window.draw(block);
    }
}



void StateGame::generateWorldFromBmp() {
    int u = 0;
    auto j = consts::blocksCountHeight;
    constexpr auto entitiesNum = consts::blocksCountHeight * consts::blocksCountWidth;

    auto& mapLoaderRef = std::get<MapLoader<Bmp>>(mapLoader);
    auto& theData =      std::get<BmpReader>(mapLoaderRef.mapReader).getData();
    auto& theEncoded =   std::get<Encoder<PixelColor>>(mapLoaderRef.encoder).encodedObjects;
    blocksNum = mapLoaderRef.getBlocksNum();
    blocks.resize(blocksNum);
    for (int k = 0; k < entitiesNum; k++) {
        if (k % consts::blocksCountWidth == 0) {
            j--;
        }
        int i = k % consts::blocksCountWidth;

        auto curID = theEncoded.find(theData[k]);
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


void StateGame::generateWorldFromTxt() {
    int u = 0;
    constexpr auto entitiesNum = consts::blocksCountHeight * consts::blocksCountWidth;

    auto& mapLoaderRef = std::get<MapLoader<Txt>>(mapLoader);
    auto& theData =      std::get<TxtReader>(mapLoaderRef.mapReader).getData();
    auto& theEncoded =   std::get<Encoder<int>>(mapLoaderRef.encoder).encodedObjects;

    blocksNum = mapLoaderRef.getBlocksNum();
    blocks.resize(blocksNum);

    for (int k = 0, j = -1; k < entitiesNum; k++) {
        int i = k % consts::blocksCountWidth;
        if (k % consts::blocksCountWidth == 0) {
            j++;
        }
        auto curID = theEncoded.find(theData[k]);
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


