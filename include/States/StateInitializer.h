#pragma once

#include <iostream>
#include "State.h"


class StateInitializer : public State {
public:
    StateInitializer() {
        std::cout << "StateInitializer::StateInitializer()" << std::endl;
    }

    void onCreate() override  {

    }

    void onDestroy() override {

    }

    void update(float dt) override {

    }
};


