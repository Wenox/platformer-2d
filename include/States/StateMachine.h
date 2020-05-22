#pragma once

#include <unordered_map>
#include <memory>
#include <Window.h>
#include "State.h"
#include "StateID.h"
#include <iostream>


class StateMachine {
public:
    StateMachine();

    void switchTo(int stateID);
    void switchToDefault();


    int insert(const std::shared_ptr<State>& state);
    void erase(int stateID);


    void processInput() const;
    void update(float dt) const;
    void draw(Window& window) const;

private:
    std::unordered_map<int, std::shared_ptr<State>> states{};
    std::shared_ptr<State> currentState{nullptr};
    int currentStateID{1}; ///* todo: rename me */
};


