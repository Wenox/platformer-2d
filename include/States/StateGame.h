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
    std::vector<std::unique_ptr<Entity>> blocks;
    Objective objective;

    Window& window;
    Camera camera;

    std::queue<res::Texture> queue;

    std::unique_ptr<MovementEvent>  moveController;
    std::unique_ptr<CollisionEvent> collider;
    std::unique_ptr<InputEvent>     inputEvent;


    bool isInDrawRange(const Entity& entity) const;
    void generateWorldFromBmp();
    void generateWorldFromTxt();
};


