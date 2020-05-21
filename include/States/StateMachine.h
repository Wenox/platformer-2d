#pragma once

#include <unordered_map>
#include <memory>
#include <Window.h>
#include "State.h"


class StateMachine {
public:
    StateMachine();

    void processInput() const;
    void update(float dt) const;
    void draw(Window& window) const;

    int insert(const std::shared_ptr<State>& state);

private:
    std::unordered_map<int, std::shared_ptr<State>> states{};
    std::shared_ptr<State> currentState{nullptr};
    int currentStateID{0};
};

