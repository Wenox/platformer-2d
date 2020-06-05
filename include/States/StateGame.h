#pragma once

#include <Entities/Entity.h>
#include "StateMachine.h"
#include "ResourceManager.h"
#include "MapLoader.h"
#include "Block.h"
#include <memory>


class StateGame : public State {
public:
    StateGame(StateMachine &stateMachine, ResourceManager& resources, std::variant<MapLoader<Bmp>, MapLoader<Txt>>& mapLoader, Window& window);

    void onCreate() override;
    void onDestroy() override;

    void processInput() override;
    void update(float dt) override;
    void draw(Window& window) override;

private:
    const int velocity = 400;
    StateMachine& stateMachine;
    ResourceManager& resources;

    std::variant<MapLoader<Bmp>, MapLoader<Txt>>& mapLoader;

    std::vector<std::unique_ptr<Entity>> blocks;
    sf::Texture texture;
    sf::Sprite sprite;

    Window& window;
    sf::View camera;

    std::queue<res::Texture> queue;

    void generateWorldFromBmp();
    void generateWorldFromTxt();
};


