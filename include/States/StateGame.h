#pragma once

#include <iostream>
#include "StateMachine.h"


class StateGame : public State {
public:
    StateGame() {
        std::cout << "StateGame::StateGame()" << std::endl;
    }

    void onCreate() override  {

    }

    void onDestroy() override {

    }

    void update(float dt) override {

    }
};


