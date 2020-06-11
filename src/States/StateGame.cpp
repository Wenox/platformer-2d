#include <Entities/Block.h>
#include "Consts.h"
#include "StateID.h"
#include "StateGame.h"

StateGame::StateGame(StateMachine &stateMachine, ResourceManager& resources, std::variant<MapLoader<Bmp>, MapLoader<Txt>>& mapLoader, Window& window)
    : stateMachine{stateMachine}
    , resources{resources}
    , mapLoader{mapLoader}
    , window{window}
    , camera{window, sf::View{{320, 288}, {static_cast<float>(window.getWindow().getSize().x), static_cast<float>(window.getWindow().getSize().y)}}}
{
    std::cout << "Here\n";
    std::visit(overload{
            [&](MapLoader<Bmp>&) { queue = std::get<MapLoader<Bmp>>(mapLoader).getQueue(); },
            [&](MapLoader<Txt>&) { queue = std::get<MapLoader<Txt>>(mapLoader).getQueue(); },
    }, mapLoader);

    std::cout << "StateGame::StateGame()" << std::endl;
    window.getWindow().setView(camera.getCamera());
}

void StateGame::onCreate() {
    std::visit(overload{
            [&](MapLoader<Bmp>&) { generateWorldFromBmp(); },
            [&](MapLoader<Txt>&) { generateWorldFromTxt(); }
    }, mapLoader);

    for (auto& block : blocks) {
        block->getSprite().setTexture(resources.getTextures().get(queue.front()));
        queue.pop();
    }

    player.getSprite().setTexture(resources.getTextures().get(res::Texture::Wizard)); /** todo: direct setter */
    camera.setController(player.getSprite());

    moveController = std::make_unique<MovementEvent>(player, blocks);
    collider = std::make_unique<CollisionEvent>(player, blocks);
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


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        player.movingState = MovingState::movingRight;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        player.movingState = MovingState::movingLeft;
    } else {
        player.movingState = MovingState::standing;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        player.jumpingState = JumpingState::jumping;
    }
}

void StateGame::update(float dt) {
    moveController->updateAxisX(dt);
    collider->updateAxisX();
    camera.updateX();


    moveController->updateAxisY(dt);
    collider->updateAxisY();
    camera.updateY();

    window.getWindow().setView(camera.getCamera());
}

void StateGame::draw(Window &window) {
    window.draw(player);
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
                player.setPosition(i * consts::entityWidth, j * consts::entityHeight);
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
                player.setPosition(i * consts::entityWidth, j * consts::entityHeight);
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


