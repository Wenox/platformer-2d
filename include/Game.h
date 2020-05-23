#pragma once


#include <States/StateMachine.h>
#include "ResourceManager.h"

class Game {
public:
    Game();

    void run();

private:
    Window window;
    ResourceManager rm;
    StateMachine stateMachine;

    sf::Clock clock;
    float dt;

    void computeDeltaTime();
    void init();

    void processInput();
    void update();
    void draw();

    bool isRunning() const;


    void testResources() {
        rm.insert("../resources/green.png");
        rm.insert("../resources/gray.png");
        rm.insert("../resources/orange.png");

        auto res1 = rm.get("../resources/green.png");
        auto res2 = rm.get("../resources/gray.png");
        auto res3 = rm.get("../resources/orange.png");

        rm.print();
    }
};


