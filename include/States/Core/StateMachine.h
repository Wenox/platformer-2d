#pragma once

#include <memory>
#include "State.h""
#include "Window.h"


class StateMachine {
public:

    void switchTo(int stateID);
    void switchToPreviousState();
    void switchToDefaultState();


    int insert(const std::shared_ptr<State>& state);
    void erase(int stateID);


    void processInput() const;
    void update(float dt) const;
    void draw(Window& window) const;


    StateMachine& operator=(int stateID);
    StateMachine& operator+=(const std::shared_ptr<State>& s);

    void setPreviousStateID(int stateID) {
        previousStateID = stateID;
    }

    int getPreviousStateID() const { return previousStateID; }

private:
    std::unordered_map<int, std::shared_ptr<State>> states{};
    std::shared_ptr<State> currentState{nullptr};

    int currentInsertedID{1};
    int previousStateID{};
};


