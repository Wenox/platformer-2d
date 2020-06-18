#pragma once

#include "StateMachine.h"
#include "RestartView.h"


class StateRestart : public State {
public:
    StateRestart(StateMachine& stateMachine, Window& window, ResourceManager& resourceManager);

    void onCreate() override;
    void onActivate() override;
    void onDeactivate() override;

    void processInput() override;
    void update(float) override;
    void draw(Window&) override;

private:
    StateMachine& stateMachine;
    Window& window;

    RestartView gui;
};