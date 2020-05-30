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
            : stateMachine{stateMachine}, resources{resources}, mapLoader{mapLoader}  // encodedObjects{mapLoader.getEncodedObjects()}
            //data{mapLoader.getData()}, blocksNum{mapLoader.getBlocksNum()}
    {
        std::cout << "INDEX: " << mapLoader.index() << std::endl;
        std::cout << "StateGame::StateGame()" << std::endl;
        std::cout << "StateGame blocksNum: " << this->blocksNum << std::endl;
    }

    void onCreate() override {

        std::cout << "u\n";
        int u = 0;
        auto j = consts::blocksCountHeight;
        constexpr auto entitiesNum = consts::blocksCountHeight * consts::blocksCountHeight;

        std::visit(overload{
                [&](MapLoader<Bmp>&) {
                    auto& mapLoaderRef = std::get<MapLoader<Bmp>>(mapLoader);
                    auto& mapReaderRef = std::get<BmpReader>(mapLoaderRef.mapReader);
                    auto& encoderRef = std::get<Encoder<PixelColor>>(mapLoaderRef.encoder);
                    auto& theData = mapReaderRef.getData();
                    auto& theEncoded = encoderRef.encodedObjects;
                    blocksNum = mapLoaderRef.getBlocksNum();
                    blocks.resize(blocksNum);
                    std::cout << "BLOCKS NUM: " << blocksNum << std::endl;
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
                [](MapLoader<Txt>&){  }
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


