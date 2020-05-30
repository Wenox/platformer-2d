#pragma once

#include "StateMachine.h"
#include "ResourceManager.h"
#include "MapLoader.h"


class StateGame : public State {
public:
    StateGame(StateMachine &stateMachine, ResourceManager& resources, std::variant<MapLoader<Bmp>, MapLoader<Txt>>& mapLoader)
            : stateMachine{stateMachine}, resources{resources}, mapLoader{mapLoader}
    {
        std::cout << "StateGame::StateGame()" << std::endl;
    }

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

    std::vector<sf::Sprite> blocks{};
    sf::Texture texture;
    sf::Sprite sprite;
    int blocksNum;

    void generateWorldFromBmp();
    void generateWorldFromTxt();
};


