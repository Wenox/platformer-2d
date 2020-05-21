#include <iostream>
#include "StateMachine.h"

StateMachine::StateMachine() {

}

void StateMachine::processInput() const {
    if (currentState) {
        currentState->processInput();
    }
}

void StateMachine::update(float dt) const {
    if (currentState) {
        currentState->update(dt);
    }
}

void StateMachine::draw(Window &window) const {
    if (currentState) {
        currentState->draw(window);
    }
}

int StateMachine::insert(const std::shared_ptr<State>& state) {
    auto inserted = states.insert(std::make_pair(currentStateID, state));
    inserted.first->second->onCreate();

    return currentStateID++;
}
