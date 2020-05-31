#pragma once

#include "StateMachine.h"
#include "ResourceManager.h"
#include "MapLoader.h"


class StateGame : public State {
public:
    StateGame(StateMachine &stateMachine, ResourceManager& resources, std::variant<MapLoader<Bmp>, MapLoader<Txt>>& mapLoader, Window& window)
            : stateMachine{stateMachine}, resources{resources}, mapLoader{mapLoader},
            window{window},
            camera{{320, 288},{ static_cast<float>(window.getWindow().getSize().x), static_cast<float>(window.getWindow().getSize().y)}},
            queue{std::get<MapLoader<Bmp>>(mapLoader).getQueue()}
    {
        std::cout << "StateGame::StateGame()" << std::endl;
        window.getWindow().setView(camera);
        camera.zoom(0.5);
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

    Window& window;
    sf::View camera;

    std::queue<res::Texture>& queue;

    void generateWorldFromBmp();
    void generateWorldFromTxt();
};


