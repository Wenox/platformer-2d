#pragma once

#include "ResourceManager.h"
#include "StateMachine.h"
#include "Settings.h"


class Game {
public:
    Game();

    void run();

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

public:

    Window& getWindow();
    ResourceManager& getResources();
    StateMachine& getStateMachine();
};


