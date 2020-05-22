#pragma once

#include <iostream>
#include <TGUI/Widgets/Label.hpp>
#include <TGUI/Gui.hpp>
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

    void draw(Window& window) override {
        sf::RectangleShape shape({400, 400});
        shape.setFillColor(sf::Color::Red);
        window.draw(shape);


        static tgui::Gui gui{window.getWindow()};
        static tgui::Label::Ptr label = tgui::Label::create("State Game");
        label->setTextSize(72);

        gui.add(label);
        gui.draw();
    }

private:
    StateMachine& stateMachine;
    Window& window;
};


