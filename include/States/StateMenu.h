#pragma once

#include <iostream>
#include "StateMachine.h"


class StateMenu : public State {
public:
    StateMenu(StateMachine& stateMachine, Window& window)
            : stateMachine{stateMachine}, window{window} {
        std::cout << "StateMenu::StateMenu()\n";
    }

    void onCreate() override  {

    }

    void onDestroy() override {

    }

    void onActivate() override {
        std::cout << "State Menu activated" << std::endl;
    }

    void processInput() override {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
            stateMachine.switchTo(2);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
            stateMachine.switchTo(3);
        }
    }

    void update(float dt) override {

    }

private:
    StateMachine& stateMachine;
    Window& window;
};


