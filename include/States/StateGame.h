#pragma once

#include "Entity.h"
#include "StateMachine.h"
#include "ResourceManager.h"
#include "MapLoader.h"
#include "Block.h"
#include "StateRestart.h"
#include <memory>
#include <Camera.h>
#include <Entities/Player/Player.h>
#include <Events/CollisionEvent.h>
#include <Events/MovementEvent.h>
#include <Entities/Objective.h>
#include <Events/InputEvent.h>
#include <GUI/HUD/LivesHUD.h>
#include <Entities/Spike.h>
#include <Entities/HeartCollectible.h>
#include <SFML/Audio/Sound.hpp>
#include <Settings.h>
#include <GUI/HUD/FpsHUD.h>


class StateGame : public State {
public:
    StateGame(StateMachine &stateMachine, ResourceManager& resources, std::variant<MapLoader<Bmp>, MapLoader<Txt>>& mapLoader, Window& window);

    void onCreate() override;
    void onDestroy() override;

    void onActivate() override;
    void onDeactivate() override;

    void processInput() override;
    void update(float dt) override;
    void draw(Window& window) override;

private:
    void updatePhysics(float dt);
    void updatePlayerLife();
    void updateGainLifeLogic();
    void updateLoseLifeLogic();
    bool canCollect(const HeartCollectible& heart);

    void updateGameStatus();
    void checkLoseCondition();
    void checkWinCondition();

    bool isInDrawRange(const Entity& entity) const;
    bool playerFellToDeath() const;
    void generateWorldFromBmp();
    void generateWorldFromTxt();

    void setEntitiesTextures();
    void setBlocksTextures();
    void setSpikesTextures();
    void setCollectiblesTextures();

    void restartGameLevel();

    StateMachine& stateMachine;
    ResourceManager& resources;

    std::variant<MapLoader<Bmp>, MapLoader<Txt>>& mapLoader;

    Player player;
    Objective objective;
    std::vector<std::unique_ptr<Entity>> blocks;
    std::vector<std::unique_ptr<Spike>> spikes;
    std::vector<std::unique_ptr<HeartCollectible>> hearts; /** todo: use interface type */

    Window& window;
    Camera camera;

    std::queue<res::Texture> blocksQueue;

    std::unique_ptr<MovementEvent>  moveController;
    std::unique_ptr<CollisionEvent> collider;
    std::unique_ptr<InputEvent>     inputEvent;

    LivesHUD livesHUD;
    FpsHUD   fpsHUD;

    sf::Sprite background;

    sf::Sound collectSound;
    sf::Sound deathSound;
    sf::Music music;

    const int bottomBorderHeight = consts::entityHeight * consts::blocksCountHeight;
};


