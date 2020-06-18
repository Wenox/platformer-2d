#pragma once

#include <SFML/Audio/Sound.hpp>
#include "MapLoader.h"
#include "StateRestart.h"
#include "Camera.h"
#include "CollisionEvent.h"
#include "MovementEvent.h"
#include "InputEvent.h"
#include "FpsHUD.h"
#include "Objective.h"
#include "Spike.h"
#include "HeartCollectible.h"


class StateGame : public State {
public:
    StateGame(StateMachine &stateMachine,
              Window& window,
              ResourceManager& resources,
              std::variant<MapLoader<Bmp>, MapLoader<Txt>>& mapLoader);

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
    Window& window;
    ResourceManager& resources;


    /** Simplifiable to WorldLoader class */
    std::variant<MapLoader<Bmp>, MapLoader<Txt>>& mapLoader;
    std::queue<res::Texture> blocksQueue;


    /** Simplifiable to World class */
    Player player;
    Objective objective;
    std::vector<std::unique_ptr<Entity>> blocks;
    std::vector<std::unique_ptr<Spike>> spikes;
    std::vector<std::unique_ptr<HeartCollectible>> hearts;
    sf::Sprite background;


    Camera camera;


    /** Simplifiable to e.g. EventsList class */
    std::unique_ptr<MovementEvent>  moveController;
    std::unique_ptr<CollisionEvent> collider;
    std::unique_ptr<InputEvent>     inputEvent;


    /** Simplifiable to HUD class */
    LivesHUD livesHUD;
    FpsHUD   fpsHUD;


    /** Simplifiable to e.g. SoundPlayer class */
    sf::Sound collectSound;
    sf::Sound deathSound;
    sf::Music music;


    const int bottomBorderHeight = consts::entityHeight * consts::blocksCountHeight;
};


