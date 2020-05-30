#pragma once

#include <iostream>
#include <TGUI/Widgets/Label.hpp>
#include <TGUI/Gui.hpp>
#include <ResourceManager/ResourceHolder.h>
#include <ResourceManager/ResourceManager.h>
#include <Encoder/PixelColor.h>
#include <Encoder/Encoder.h>
#include <Encoder/MapLoader.h>
#include "StateMachine.h"
#include "Consts.h"


class StateGame : public State {
public:
    StateGame(StateMachine &stateMachine, ResourceManager& resources, std::variant<MapLoader<Bmp>, MapLoader<Txt>>& mapLoader)
            : stateMachine{stateMachine}, resources{resources}, mapLoader{mapLoader}
    {
        std::cout << "StateGame::StateGame()" << std::endl;
    }

    void onCreate() override {
        int u = 0;
        auto j = consts::blocksCountHeight;
        constexpr auto entitiesNum = consts::blocksCountHeight * consts::blocksCountWidth;
        std::cout << "BlocksCountNum: " << entitiesNum << std::endl;

        std::visit(overload{
                [&](MapLoader<Bmp>&) {
                    auto& mapLoaderRef = std::get<MapLoader<Bmp>>(mapLoader);
                    auto& theData =      std::get<BmpReader>(mapLoaderRef.mapReader).getData();
                    auto& theEncoded =   std::get<Encoder<PixelColor>>(mapLoaderRef.encoder).encodedObjects;
                    blocksNum = mapLoaderRef.getBlocksNum();
                    blocks.resize(blocksNum);
                    for (int k = 0; k < entitiesNum; k++) {
                        if (k % consts::blocksCountWidth == 0) {
                            j--;
                        }
                        int i = k % consts::blocksCountWidth;

                        auto curID = theEncoded.find(theData[k]);
                        switch (curID->second) {
                            case Obj::Entity::Empty:
                                break;
                            case Obj::Entity::Block:
                                blocks[u].setPosition(i * consts::entityWidth, j * consts::entityHeight);
                                u++;
                                break;
                            default:
                                break;
                        }
                    }
                    },
                [&](MapLoader<Txt>&){
                    {
                        auto& mapLoaderRef = std::get<MapLoader<Txt>>(mapLoader);
                        auto& theData =      std::get<TxtReader>(mapLoaderRef.mapReader).getData();
                        auto& theEncoded =   std::get<Encoder<int>>(mapLoaderRef.encoder).encodedObjects;

                        blocksNum = mapLoaderRef.getBlocksNum();
                        blocks.resize(blocksNum);

                        j = -1;
                        std::cout << "EntitiesNum: " << entitiesNum << std::endl;
                        for (int k = 0; k < entitiesNum; k++) {
                            int i = k % consts::blocksCountWidth;
                            if (k % consts::blocksCountWidth == 0) {
                                j++;
                            }
                            auto curID = theEncoded.find(theData[k]);
                            switch (curID->second) {
                                case Obj::Entity::Empty:
                                    break;
                                case Obj::Entity::Block:
                                    std::cout << "(x, y, i, j, k, u)\n";
                                    std::cout << i * consts::entityWidth << " " << j * consts::entityHeight << " " << i << " " << j << " " << k << " " << u << std::endl;
                                    blocks[u].setPosition(i * consts::entityWidth, j * consts::entityHeight);
                                    u++;
                                    break;
                                default:
                                    break;
                            }
                        }
                    }
                }
        }, mapLoader);



        for (auto& block : blocks) {
            block.setTexture(resources.getTextures().get(res::Texture::Block));
        }
        texture = resources.getTextures().get(res::Texture::Wizard);
        sprite.setTexture(texture);



    }
    void onDestroy() override {}

    void onActivate() override {
        sprite.setTexture(resources.getTextures()[res::Texture::Wizard]);
    }

    void processInput() override {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
            stateMachine.switchTo(state::initID);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
            stateMachine.switchTo(state::menuID);
        }
    }
    void update(float dt) override {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            sprite.move({-velocity * dt, 0});
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            sprite.move({velocity * dt, 0});
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            sprite.move({0, -velocity * dt});
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            sprite.move({0, velocity * dt});
        }
    }
    void draw(Window& window) override {
        window.draw(sprite);
        for (const auto& block : blocks) {
            window.draw(block);
        }
    }

private:
    int c{0};
    const int velocity = 200;
    StateMachine& stateMachine;
    ResourceManager& resources;

    std::variant<MapLoader<Bmp>, MapLoader<Txt>>& mapLoader;

    std::vector<sf::Sprite> blocks{};
    sf::Texture texture;
    sf::Sprite sprite;
    int blocksNum;
};


