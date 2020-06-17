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
    void updatePlayerLife();
    void updateGainLifeLogic();
    void updateLoseLifeLogic();

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

    std::queue<res::Texture> queue;

    std::unique_ptr<MovementEvent>  moveController;
    std::unique_ptr<CollisionEvent> collider;
    std::unique_ptr<InputEvent>     inputEvent;

    LivesHUD livesHUD;
    FpsHUD   fpsHUD;

    sf::Sprite bg;

    sf::Sound collectSound;
    sf::Sound deathSound;


    bool isInDrawRange(const Entity& entity) const;
    void generateWorldFromBmp();
    void generateWorldFromTxt();

    void setEntitiesTextures();
    void setBlocksTextures();
    void setSpikesTextures();
    void setCollectiblesTextures();

    void restartGameLevel();

    std::string calcCurrentFps(float dt);

    sf::Music music;
};


