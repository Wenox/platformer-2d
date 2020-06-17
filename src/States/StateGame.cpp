#include "Block.h"
#include "Consts.h"
#include "StateID.h"
#include "StateGame.h"


StateGame::StateGame(StateMachine &stateMachine, ResourceManager& resources, std::variant<MapLoader<Bmp>, MapLoader<Txt>>& mapLoader, Window& window)
        : stateMachine{stateMachine}
        , resources{resources}
        , mapLoader{mapLoader}
        , window{window}
        , camera{sf::View{{320, 288}, {static_cast<float>(window.getWindow().getSize().x), static_cast<float>(window.getWindow().getSize().y)}}}
        , livesHUD(window.getWindow(), resources.getTextures())
        , background(resources.getTextures()[res::Texture::BgGame])
        , collectSound(resources.getSounds()[res::Sound::Bullet])
        , deathSound(resources.getSounds()[res::Sound::Death])
{
    music.openFromFile(consts::gameMusic.data());

    std::visit(overload{
            [&](MapLoader<Bmp>&) { blocksQueue = std::get<MapLoader<Bmp>>(mapLoader).getQueue(); },
            [&](MapLoader<Txt>&) { blocksQueue = std::get<MapLoader<Txt>>(mapLoader).getQueue(); },
    }, mapLoader);
}

void StateGame::onCreate() {
    std::visit(overload{
            [&](MapLoader<Bmp>&) { generateWorldFromBmp(); },
            [&](MapLoader<Txt>&) { generateWorldFromTxt(); }
    }, mapLoader);

    this->setEntitiesTextures();

    camera.setController(player);

    moveController = std::make_unique<MovementEvent>(player, blocks);
    collider       = std::make_unique<CollisionEvent>(player, blocks);
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
    const auto &heartTexture = resources.getTextures()[res::Texture::Heart];
    for (const auto &heart : hearts) {
        /** todo: set texture during construction of hearts */
        heart->getSprite().setTexture(heartTexture);
    }
}

void StateGame::onActivate() {
    if (state::restartID == stateMachine.getPreviousStateID()) {
        restartGameLevel();
    }

    music.play();
    deathSound.setVolume(mySettings.volume);
    collectSound.setVolume(mySettings.volume);
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
    player.jumpingState = JumpingState::onGround;
    player.movingState  = MovingState::standing;
    player.restartJumpTime();

    livesHUD.refillLives();

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
    fpsHUD.update(dt);

    updatePlayerLife();
    updateGameStatus();
}

void StateGame::updatePhysics(float dt) {
    moveController->updateAxisX(dt);
    collider->updateAxisX(dt);
    camera.updateX();

    moveController->updateAxisY(dt);
    collider->updateAxisY(dt);
    camera.updateY();
}

void StateGame::updatePlayerLife() {
    updateLoseLifeLogic();
    updateGainLifeLogic();
}

void StateGame::updateLoseLifeLogic() {
    if (playerFellToDeath()) {
        player.kill(livesHUD);
        deathSound.play();
    }

    for (const auto& spike : spikes) {
        if (player.isIntersecting(*spike)) {
            player.kill(livesHUD);
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
            livesHUD.increaseLife();
            heart->setCollected(true);
            collectSound.play();
        }
    }
}

bool StateGame::canCollect(const HeartCollectible& heart) {
    return !heart.wasCollected() and player.isIntersecting(heart) and !livesHUD.hasAllLives();
}

void StateGame::updateGameStatus() {
    checkLoseCondition();
    checkWinCondition();
}

void StateGame::checkWinCondition() {
    if (player.isIntersecting(objective)) {
        consts::playerWon = true;
        stateMachine = state::restartID;
    }
}

void StateGame::checkLoseCondition() {
    if (livesHUD.isDead()) {
        consts::playerWon = false;
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
    window.draw(livesHUD);

    if (mySettings.isFpsEnabled) {
        window.draw(fpsHUD);
    }
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


