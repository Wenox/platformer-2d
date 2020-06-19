#include "StateGame.h"
#include "StateID.h"
#include "Settings.h"


StateGame::StateGame(StateMachine &stateMachine,
                     Window& window,
                     ResourceManager& resources,
                     std::variant<MapLoader<Bmp>, MapLoader<Txt>>& mapLoader)

        : stateMachine{stateMachine}
        , window{window}
        , resources{resources}
        , mapLoader{mapLoader}
        , background(resources.getTextures()[res::Texture::BgGame])
        , camera{sf::View{{window.getWidth() / 2.0f, window.getHeight() / 2.0f},
                          {static_cast<float>(window.getWidth()),
                           static_cast<float>(window.getHeight())}}}
        , lives(window.getWindow(), resources.getTextures())
        , collectSound(resources.getSounds()[res::Sound::Collect])
        , deathSound(resources.getSounds()[res::Sound::Death])
        , winGameSound(resources.getSounds()[res::Sound::WinGame])
{
    loadMusic();

    std::visit(overload{
            [&](MapLoader<Bmp>&) { blocksQueue = std::get<MapLoader<Bmp>>(mapLoader).getQueue(); },
            [&](MapLoader<Txt>&) { blocksQueue = std::get<MapLoader<Txt>>(mapLoader).getQueue(); },
    }, mapLoader);
}

void StateGame::loadMusic() {
    music.openFromFile(config::gameMusic.data());
}

void StateGame::onCreate() {
    std::visit(overload{
            [&](MapLoader<Bmp>&) { generateWorldFromBmp(); },
            [&](MapLoader<Txt>&) { generateWorldFromTxt(); }
    }, mapLoader);

    this->setEntitiesTextures();

    camera.setController(player);

    movementsEvent = std::make_unique<MovementEvent>(player, blocks);
    collisionEvent = std::make_unique<CollisionEvent>(player, blocks);
    inputEvent     = std::make_unique<InputEvent>(player, resources, window);
}

void StateGame::setEntitiesTextures() {
    this->setBlocksTextures();
    this->setSpikesTextures();
    this->setCollectiblesTextures();

    player.getSprite().setTexture(resources.getTextures().get(res::Texture::Player)); /** todo: direct setter */
    objective.getSprite().setTexture(resources.getTextures().get(res::Texture::Objective));
}


void StateGame::setBlocksTextures() {
    for (const auto& block : blocks) {
        block->getSprite().setTexture(resources.getTextures()[blocksQueue.front()]);
        blocksQueue.pop();
    }
}

void StateGame::setSpikesTextures() {
    const auto& spikeTexture = resources.getTextures()[res::Texture::Spike];
    for (const auto& spike : spikes) {
        spike->getSprite().setTexture(spikeTexture);
        spike->setTextureDirection();
    }
}

void StateGame::setCollectiblesTextures() {
    const auto& heartTexture = resources.getTextures()[res::Texture::Heart];
    for (const auto &heart : hearts) {
        heart->getSprite().setTexture(heartTexture);
    }
}

void StateGame::onActivate() {
    if (state::restartID == stateMachine.getPreviousStateID()) {
        restartGameLevel();
    }

    music.play();
    deathSound.setVolume(audioConfig.volume);
    collectSound.setVolume(audioConfig.volume);
    winGameSound.setVolume(audioConfig.volume);
}

void StateGame::onDeactivate() {
    music.pause();
    stateMachine.setPreviousStateID(state::gameID);
}

void StateGame::onDestroy() {
    music.stop();
}

void StateGame::restartGameLevel() {
    player.setPosition(player.getStartingPosition());
    player.movingState  = MovingState::standing;
    player.landOnGroundUpdate();

    lives.refillLives();

    /** Respawn collectibles */
    for (const auto& heart : hearts) {
        if (heart->wasCollected()) {
            heart->setCollected(false);
        }
    }
}

void StateGame::processInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
        stateMachine = state::pausedID;
    }

    inputEvent->update();
}

void StateGame::update(float dt) {
    updatePhysics(dt);

    window.updateView(camera.getCameraView());
    fps.update(dt);

    updatePlayerLife();
    updateGameStatus();
}

void StateGame::updatePhysics(float dt) {
    movementsEvent->updateAxisX(dt);
    collisionEvent->updateAxisX(dt);
    camera.updateX();

    movementsEvent->updateAxisY(dt);
    collisionEvent->updateAxisY(dt);
    camera.updateY();
}

void StateGame::updatePlayerLife() {
    updateLoseLifeLogic();
    updateGainLifeLogic();
}

void StateGame::updateLoseLifeLogic() {
    if (playerFellToDeath()) {
        player.kill(lives);
        deathSound.play();
    }

    for (const auto& spike : spikes) {
        if (player.isIntersecting(*spike)) {
            player.kill(lives);
            deathSound.play();
        }
    }
}

bool StateGame::playerFellToDeath() const {
    return player.top() > bottomBorderHeight;
}

void StateGame::updateGainLifeLogic() {
    for (const auto& heart : hearts) {
        if (canCollect(*heart)) {
            lives.increaseLife();
            heart->setCollected(true);
            collectSound.play();
        }
    }
}

bool StateGame::canCollect(const HeartCollectible& heart) {
    return !heart.wasCollected() and player.isIntersecting(heart) and !lives.hasAllLives();
}

void StateGame::updateGameStatus() {
    checkLoseCondition();
    checkWinCondition();
}

void StateGame::checkWinCondition() {
    if (player.isIntersecting(objective)) {
        config::playerWon = true;
        winGameSound.play();
        stateMachine = state::restartID;
    }
}

void StateGame::checkLoseCondition() {
    if (lives.isDead()) {
        config::playerWon = false;
        stateMachine = state::restartID;
    }
}


void StateGame::draw(Window& window) {
    window.draw(background);
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
    window.draw(lives);

    if (audioConfig.isFpsEnabled) {
        window.draw(fps);
    }
}


bool StateGame::isInDrawRange(const Entity& entity) const {
    return std::abs(entity.left() - player.left()) < 640.0f
        && std::abs(entity.top()  - player.top())  < 576.0f;
}

void StateGame::generateWorldFromBmp() {
    int u = 0;
    auto j = config::blocksCountHeight;
    const auto entitiesNum = config::blocksCountHeight * config::blocksCountWidth;

    auto& mapLoaderRef = std::get<MapLoader<Bmp>>(mapLoader);
    auto& theData =      std::get<BmpReader>(mapLoaderRef.mapReader).getData();
    auto& theEncoded =   std::get<Encoder<PixelColor>>(mapLoaderRef.encoder).encodedObjects;

    for (int k = 0; k < entitiesNum; k++) {
        if (k % config::blocksCountWidth == 0) {
            j--;
        }
        int i = k % config::blocksCountWidth;

        auto curID = theEncoded.find(theData[k]);
        switch (curID->second) {
            case Obj::Entity::Empty:
                break;
            case Obj::Entity::Player:
                player.setPosition(i * config::entityWidth, j * config::entityHeight);
                player.setStartingPosition();
                break;
            case Obj::Entity::Objective:
                objective.setPosition(i * config::entityWidth, j * config::entityHeight);
                break;
            case Obj::Entity::HeartCollectible:
                hearts.push_back(std::move(std::make_unique<HeartCollectible>(sf::Vector2f{static_cast<float>(i * config::entityWidth),
                                                                                           static_cast<float>(j * config::entityHeight)})));
                break;
            case Obj::Entity::Spike:
                spikes.push_back(std::move(std::make_unique<Spike>(Obj::Entity::Spike, sf::Vector2f{static_cast<float>(i * config::entityWidth),
                                                                                                    static_cast<float>(j * config::entityHeight)})));
                break;
            case Obj::Entity::SpikeLeft:
                spikes.push_back(std::move(std::make_unique<Spike>(Obj::Entity::SpikeLeft, sf::Vector2f{static_cast<float>(i * config::entityWidth),
                                                                                                        static_cast<float>(j * config::entityHeight)})));
                break;
            case Obj::Entity::SpikeRight:
                spikes.push_back(std::move(std::make_unique<Spike>(Obj::Entity::SpikeRight, sf::Vector2f{static_cast<float>(i * config::entityWidth),
                                                                                                         static_cast<float>(j * config::entityHeight)})));
                break;
            case Obj::Entity::SpikeTop:
                spikes.push_back(std::move(std::make_unique<Spike>(Obj::Entity::SpikeTop, sf::Vector2f{static_cast<float>(i * config::entityWidth),
                                                                                                       static_cast<float>(j * config::entityHeight)})));
                break;
            default:
                auto newBlock = std::make_unique<Block>(sf::Vector2f{static_cast<float>(i * config::entityWidth),
                                                                     static_cast<float>(j * config::entityHeight)});
                blocks.push_back(std::move(newBlock));
                u++;
                break;
        }
    }
}


void StateGame::generateWorldFromTxt() {
    int u = 0;
    const auto entitiesNum = config::blocksCountHeight * config::blocksCountWidth;

    auto& mapLoaderRef = std::get<MapLoader<Txt>>(mapLoader);
    auto& theData =      std::get<TxtReader>(mapLoaderRef.mapReader).getData();
    auto& theEncoded =   std::get<Encoder<int>>(mapLoaderRef.encoder).encodedObjects;

    for (int k = 0, j = -1; k < entitiesNum; k++) {
        int i = k % config::blocksCountWidth;
        if (k % config::blocksCountWidth == 0) {
            j++;
        }
        auto curID = theEncoded.find(theData[k]);
        switch (curID->second) {
            case Obj::Entity::Empty:
                break;
            case Obj::Entity::Player:
                player.setPosition(i * config::entityWidth, j * config::entityHeight);
                player.setStartingPosition();
                break;
            case Obj::Entity::Objective:
                objective.setPosition(i * config::entityWidth, j * config::entityHeight);
                break;
            case Obj::Entity::HeartCollectible:
                hearts.push_back(std::move(std::make_unique<HeartCollectible>(sf::Vector2f{static_cast<float>(i * config::entityWidth),
                                                                                           static_cast<float>(j * config::entityHeight)})));
                break;
            case Obj::Entity::Spike:
                spikes.push_back(std::move(std::make_unique<Spike>(Obj::Entity::Spike, sf::Vector2f{static_cast<float>(i * config::entityWidth),
                                                                                                    static_cast<float>(j * config::entityHeight)})));
                break;
            case Obj::Entity::SpikeLeft:
                spikes.push_back(std::move(std::make_unique<Spike>(Obj::Entity::SpikeLeft, sf::Vector2f{static_cast<float>(i * config::entityWidth),
                                                                                                        static_cast<float>(j * config::entityHeight)})));
                break;
            case Obj::Entity::SpikeRight:
                spikes.push_back(std::move(std::make_unique<Spike>(Obj::Entity::SpikeRight, sf::Vector2f{static_cast<float>(i * config::entityWidth),
                                                                                                         static_cast<float>(j * config::entityHeight)})));
                break;
            case Obj::Entity::SpikeTop:
                spikes.push_back(std::move(std::make_unique<Spike>(Obj::Entity::SpikeTop, sf::Vector2f{static_cast<float>(i * config::entityWidth),
                                                                                                       static_cast<float>(j * config::entityHeight)})));
                break;
            default:
                auto newBlock = std::make_unique<Block>(sf::Vector2f{static_cast<float>(i * config::entityWidth),
                                                                     static_cast<float>(j * config::entityHeight)});
                blocks.push_back(std::move(newBlock));
                u++;
                break;
        }
    }
}


