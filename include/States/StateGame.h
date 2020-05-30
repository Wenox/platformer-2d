#pragma once

#include <iostream>
#include <TGUI/Widgets/Label.hpp>
#include <TGUI/Gui.hpp>
#include <ResourceManager/ResourceHolder.h>
#include <ResourceManager/ResourceManager.h>
#include <Encoder/PixelColor.h>
#include <Encoder/Encoder.h>
#include "StateMachine.h"


class StateGame : public State {
public:

    StateGame(StateMachine& stateMachine,
              ResourceManager& resources,
              int blocksNum,
              std::map<PixelColor, Obj::Entity>& encodedObjects,
              std::vector<PixelColor>& data);

    void onCreate() override;
    void onDestroy() override;

    void onActivate() override;

    void processInput() override;
    void update(float dt) override;
    void draw(Window& window) override;

private:
    int c{0};
    const int velocity = 200;
    StateMachine& stateMachine;
    ResourceManager& resources;
    std::map<PixelColor, Obj::Entity>& encodedObjects;
    std::vector<PixelColor>& data;
    std::vector<sf::Sprite> blocks;
    sf::Texture texture;
    sf::Sprite sprite;
    int blocksNum;
};


