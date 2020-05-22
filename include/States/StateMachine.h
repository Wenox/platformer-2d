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

    StateMachine& operator=(int stateID) {
        this->switchTo(stateID);
        return *this;
    }

    int insert(const std::shared_ptr<State>& state);
    void erase(int stateID);


    void processInput() const;
    void update(float dt) const;
    void draw(Window& window) const;

    StateMachine& operator+=(const std::shared_ptr<State>& s) {
        auto it = states.insert(std::make_pair(currentStateID, s));
        it.first->second->onCreate();
        currentStateID++;
        return *this;
    }

private:
    std::unordered_map<int, std::shared_ptr<State>> states{};
    std::shared_ptr<State> currentState{nullptr};
    int currentStateID{1}; ///* todo: rename me */
};


