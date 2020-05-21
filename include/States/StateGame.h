#pragma once

#include <iostream>
#include "StateMachine.h"


class StateGame : public State {
public:
    StateGame(StateMachine& stateMachine, Window& window)
            : stateMachine{stateMachine}, window{window} {
        std::cout << "StateGame::StateGame()" << std::endl;
    }

    void onCreate() override  {

    }

    void onDestroy() override {

    }

    void onActivate() override {
        std::cout << "State Game activated" << std::endl;
    }

    void processInput() override {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
            stateMachine.switchTo(3);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
            stateMachine.switchTo(1);
        }
    }

    void update(float dt) override {

    }

private:
    StateMachine& stateMachine;
    Window& window;
};


