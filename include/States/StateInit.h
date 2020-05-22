#pragma once

#include <iostream>
#include <TGUI/Widgets/Label.hpp>
#include <TGUI/Gui.hpp>
#include "StateMachine.h"


class StateInit : public State {
public:
    StateInit(StateMachine& stateMachine, Window& window);

    void onCreate() override;
    void onDestroy() override;

    void onActivate() override;

    void processInput() override;
    void update(float dt) override;
    void draw(Window& window) override;

private:
    StateMachine& stateMachine;
    Window& window;
};


