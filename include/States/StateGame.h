#pragma once

#include <Entities/Entity.h>
#include "StateMachine.h"
#include "ResourceManager.h"
#include "MapLoader.h"
#include "Block.h"
#include <memory>
#include <Camera.h>
#include <Entities/Player.h>
#include <Events/CollisionEvent.h>


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
    sf::Texture texture;

    Window& window;
    Camera camera;

    std::queue<res::Texture> queue;

    std::unique_ptr<CollisionEvent> collider;

    void generateWorldFromBmp();
    void generateWorldFromTxt();
};


