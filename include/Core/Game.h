#pragma once

#include "ResourceManager.h"
#include "States/Core/StateMachine.h"
#include "Settings.h"


class Game {
public:
    Game();

    void run();

    auto& getWindow()  {
        return window;
    }
    auto& getResources()  {
        return resources;
    }
    auto& getStateMachine()  {
        return stateMachine;
    }
private:
    Window window;
    ResourceManager resources;
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


