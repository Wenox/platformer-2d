#pragma once

#include <iostream>
#include <MenuGUI.h>
#include "StateMachine.h"
#include "TGUI/Gui.hpp"
#include "TGUI/TGUI.hpp"

#include <SFML/Audio.hpp>

class StateMenu : public State {
public:
    StateMenu(StateMachine& stateMachine, Window& window);

    void onCreate() override;
    void onDestroy() override;

    void onActivate() override;
    void onDeactivate() override;

    void processInput() override;
    void update(float dt) override;
    void draw(Window&) override;

private:
    StateMachine& stateMachine;
    Window& window;
    MenuGUI gui;
};


