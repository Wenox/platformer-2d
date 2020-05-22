#pragma once


#include <States/StateMachine.h>

class Game {
public:
    Game();

    void run();

private:
    Window window;
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


