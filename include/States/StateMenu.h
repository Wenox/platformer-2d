#pragma once

#include <iostream>
#include "StateMachine.h"
#include "TGUI/Gui.hpp"
#include "TGUI/Widgets/Label.hpp"

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

    void draw(Window& window) override {
        sf::RectangleShape shape({400, 400});
        shape.setFillColor(sf::Color::Blue);

        window.draw(shape);

        static tgui::Gui gui{window.getWindow()};
        static tgui::Label::Ptr label = tgui::Label::create("State Menu");
        label->setTextSize(72);

        gui.add(label);
        gui.draw();
    }

private:
    StateMachine& stateMachine;
    Window& window;
};


