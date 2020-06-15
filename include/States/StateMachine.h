#pragma once

#include "State.h"
#include <memory>
#include "Window.h"


class StateMachine {
public:

    void switchTo(int stateID);
    void switchToDefault();


    int insert(const std::shared_ptr<State>& state);
    void erase(int stateID);


    void processInput() const;
    void update(float dt) const;
    void draw(Window& window) const;


    StateMachine& operator=(int stateID);
    StateMachine& operator+=(const std::shared_ptr<State>& s);

    void setCameFrom(int id) {
        cameFromState = id;
    }

    int getCameFrom() const { return cameFromState; }

private:
    std::unordered_map<int, std::shared_ptr<State>> states{};
    std::shared_ptr<State> currentState{nullptr};
    int currentStateID{1}; ///* todo: rename me */

    int cameFromState{};
};


