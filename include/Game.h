#pragma once


#include "ResourceManager/ResourceManager.h"
#include <States/StateMachine.h>

class Game {
public:
    Game();

    void run();

private:
    Window window;
    ResourceManager resourcesPool;
    StateMachine stateMachine;

    sf::Clock clock;
    float dt;

    void computeDeltaTime();
    void init();

    void processInput();
    void update();
    void draw();

    bool isRunning() const;

};


