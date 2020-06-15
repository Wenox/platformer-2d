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
    , livesHUD(window.getWindow(), resources.getTextures())
    , bg(resources.getTextures()[res::Texture::BgClouds])
    , sound(resources.getSounds().get(res::Sound::Bullet))
    , deathSound(resources.getSounds().get(res::Sound::Death))
{
    bg.scale(1.4, 1.4);
    std::visit(overload{
            [&](MapLoader<Bmp>&) { queue = std::get<MapLoader<Bmp>>(mapLoader).getQueue(); },
            [&](MapLoader<Txt>&) { queue = std::get<MapLoader<Txt>>(mapLoader).getQueue(); },
    }, mapLoader);

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

    for (auto& spike : spikes) {
        spike->getSprite().setTexture(resources.getTextures().get(res::Texture::Spike));
        spike->setTextureDirection();
    }

    for (auto& heart : hearts) {
        /** todo: set texture during construction of hearts */
        heart->getSprite().setTexture(resources.getTextures()[res::Texture::Heart]);
    }

    player.getSprite().setTexture(resources.getTextures().get(res::Texture::Player)); /** todo: direct setter */
    objective.getSprite().setTexture(resources.getTextures().get(res::Texture::Objective));

    camera.setController(player.getSprite());

    moveController = std::make_unique<MovementEvent>(player, blocks);
    collider = std::make_unique<CollisionEvent>(player, blocks);
    inputEvent = std::make_unique<InputEvent>(player, resources, window);

    prepareFPS();
}


void StateGame::onDestroy() {

}

void StateGame::onActivate() {
    stateMachine.setCameFrom(state::gameID);
}

void StateGame::processInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
        stateMachine.switchTo(state::initID);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
        stateMachine.switchTo(state::menuID);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
        stateMachine = state::pausedID;
    }

    inputEvent->update();
}

void StateGame::update(float dt) {
    moveController->updateAxisX(dt);
    collider->updateAxisX(dt);
    camera.updateX();

    moveController->updateAxisY(dt);
    collider->updateAxisY(dt);
    camera.updateY();


    for (const auto& spike : spikes) {
        if (player.isIntersecting(*spike)) {
            deathSound.play();
            player.kill(livesHUD);
        }
    }

    for (const auto& heart : hearts) {
        if (!heart->wasCollected()) {
            if (player.isIntersecting(*heart) and !livesHUD.hasAllLives()) {
                sound.play();
                livesHUD.increaseLife();
                heart->setCollected(true);
            }
        }
    }


    window.getWindow().setView(camera.getCamera());

    if (livesHUD.isDead()) {
        stateMachine = state::menuID;
    }

    fps.setString(std::to_string(static_cast<int>(1 / dt)));
}

void StateGame::draw(Window& window) {
    window.draw(bg);
    for (const auto& block : blocks) {
        if (isInDrawRange(*block)) {
            window.draw(*block);
        }
    }
    for (const auto& spike : spikes) {
        if (isInDrawRange(*spike)) {
            window.draw(*spike);
        }
    }
    for (const auto& heart : hearts) {
        if (isInDrawRange(*heart) and !heart->wasCollected()) {
            window.draw(*heart);
        }
    }
    window.draw(objective);
    window.draw(player);
    window.draw(livesHUD);

    if (mySettings.isFpsEnabled) {
        window.draw(fps);
    }
}

void StateGame::prepareFPS() {
    if (!font.loadFromFile("../resources/CascadiaCode.ttf"))
        throw std::runtime_error{"Font cascadiaCode missing"};
    fps.setFont(font);
    fps.setCharacterSize(36);
    fps.setPosition(0, 960);
    fps.setFillColor(sf::Color::Yellow);
    fps.setOutlineColor(sf::Color::Black);
    fps.setOutlineThickness(1);
}
bool StateGame::isInDrawRange(const Entity& entity) const {
    return std::abs(entity.left() - player.left()) < 640.0f
        && std::abs(entity.top()  - player.top())  < 576.0f;
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
                player.setStartingPosition();
                break;
            case Obj::Entity::Objective:
                objective.setPosition(i * consts::entityWidth, j * consts::entityHeight);
                break;
            case Obj::Entity::HeartCollectible:
                hearts.push_back(std::move(std::make_unique<HeartCollectible>(sf::Vector2f{static_cast<float>(i * consts::entityWidth),
                                                                                                       static_cast<float>(j * consts::entityHeight)})));
                break;
            case Obj::Entity::Spike:
                spikes.push_back(std::move(std::make_unique<Spike>(Obj::Entity::Spike, sf::Vector2f{static_cast<float>(i * consts::entityWidth),
                                                                                                    static_cast<float>(j * consts::entityHeight)})));
                break;
            case Obj::Entity::SpikeLeft:
                spikes.push_back(std::move(std::make_unique<Spike>(Obj::Entity::SpikeLeft, sf::Vector2f{static_cast<float>(i * consts::entityWidth),
                                                                                                        static_cast<float>(j * consts::entityHeight)})));
                break;
            case Obj::Entity::SpikeRight:
                spikes.push_back(std::move(std::make_unique<Spike>(Obj::Entity::SpikeRight, sf::Vector2f{static_cast<float>(i * consts::entityWidth),
                                                                                                         static_cast<float>(j * consts::entityHeight)})));
                break;
            case Obj::Entity::SpikeTop:
                spikes.push_back(std::move(std::make_unique<Spike>(Obj::Entity::SpikeTop, sf::Vector2f{static_cast<float>(i * consts::entityWidth),
                                                                                                       static_cast<float>(j * consts::entityHeight)})));
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
                player.setStartingPosition();
                break;
            case Obj::Entity::Objective:
                objective.setPosition(i * consts::entityWidth, j * consts::entityHeight);
                break;
            case Obj::Entity::HeartCollectible:
                hearts.push_back(std::move(std::make_unique<HeartCollectible>(sf::Vector2f{static_cast<float>(i * consts::entityWidth),
                                                                                           static_cast<float>(j * consts::entityHeight)})));
                break;
            case Obj::Entity::Spike:
                spikes.push_back(std::move(std::make_unique<Spike>(Obj::Entity::Spike, sf::Vector2f{static_cast<float>(i * consts::entityWidth),
                                                                                     static_cast<float>(j * consts::entityHeight)})));
                break;
            case Obj::Entity::SpikeLeft:
                spikes.push_back(std::move(std::make_unique<Spike>(Obj::Entity::SpikeLeft, sf::Vector2f{static_cast<float>(i * consts::entityWidth),
                                                                                                    static_cast<float>(j * consts::entityHeight)})));
                break;
            case Obj::Entity::SpikeRight:
                spikes.push_back(std::move(std::make_unique<Spike>(Obj::Entity::SpikeRight, sf::Vector2f{static_cast<float>(i * consts::entityWidth),
                                                                                                    static_cast<float>(j * consts::entityHeight)})));
                break;
            case Obj::Entity::SpikeTop:
                spikes.push_back(std::move(std::make_unique<Spike>(Obj::Entity::SpikeTop, sf::Vector2f{static_cast<float>(i * consts::entityWidth),
                                                                                                    static_cast<float>(j * consts::entityHeight)})));
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


