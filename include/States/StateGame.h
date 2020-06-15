#pragma once

#include <Entities/Entity.h>
#include "StateMachine.h"
#include "ResourceManager.h"
#include "MapLoader.h"
#include "Block.h"
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


class StateGame : public State {
public:
    StateGame(StateMachine &stateMachine, ResourceManager& resources, std::variant<MapLoader<Bmp>, MapLoader<Txt>>& mapLoader, Window& window);

    void onCreate() override;
    void onDestroy() override;

    void processInput() override;
    void update(float dt) override;
    void draw(Window& window) override;

private:
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

    sf::Sprite bg;

    sf::Sound sound;
    sf::Sound deathSound;

    sf::Font font;
    sf::Text fps;

    bool isInDrawRange(const Entity& entity) const;
    void generateWorldFromBmp();
    void generateWorldFromTxt();

    void prepareFPS();
};


