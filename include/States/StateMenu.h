#pragma once

#include <iostream>
#include "State.h"


class StateMenu : public State {
public:
    StateMenu() {
        std::cout << "StateMenu::StateMenu()\n";
    }

    void onCreate() override  {

    }

    void onDestroy() override {

    }

    void update(float dt) override {

    }
};


