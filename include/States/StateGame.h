#pragma once

#include <iostream>
#include <TGUI/Widgets/Label.hpp>
#include <TGUI/Gui.hpp>
#include "StateMachine.h"


class StateGame : public State {
public:
    explicit StateGame(StateMachine& stateMachine);

    void onCreate() override;
    void onDestroy() override;

    void onActivate() override;

    void processInput() override;
    void update(float dt) override;
    void draw(Window& window) override;

private:
    StateMachine& stateMachine;
};


