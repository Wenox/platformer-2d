#pragma once

#include <iostream>
#include "StateMachine.h"
#include "TGUI/Gui.hpp"
#include "TGUI/Widgets/Label.hpp"

class StateMenu : public State {
public:
    StateMenu(StateMachine& stateMachine, Window& window);

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


