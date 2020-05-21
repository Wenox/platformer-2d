#pragma once

#include <iostream>
#include "StateMachine.h"


class StateInitializer : public State {
public:
    StateInitializer(StateMachine& stateMachine, Window& window)
    : stateMachine{stateMachine}, window{window} {
        std::cout << "StateInitializer::StateInitializer()" << std::endl;
    }

    void onCreate() override  {

    }

    void onDestroy() override {

    }

    void onActivate() override {
        std::cout << "State Initializer activated" << std::endl;
    }

    void processInput() override {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
            stateMachine.switchTo(2);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
            stateMachine.switchTo(1);
        }
    }

    void update(float dt) override {

    }

    void draw(Window& window) override {
        sf::Text text;
        text.setString("State Initializer");
        window.draw(text);
    }



private:
    StateMachine& stateMachine;
    Window& window;
};


