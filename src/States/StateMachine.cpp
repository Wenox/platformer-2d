#include <iostream>
#include "StateMachine.h"


void StateMachine::switchTo(int stateID) {
    auto it = states.find(stateID);
    if (it != std::end(states)) {
        if (currentState) {
            currentState->onDeactivate();
        }
        currentState = it->second;
        currentState->onActivate();
    } else {
        std::cerr << "Cannot switchTo stateID: " << stateID << std::endl;
        ///* todo: throw BadSwitchStateID */
    }
}

void StateMachine::switchToDefault() {

}

StateMachine& StateMachine::operator=(int stateID) {
    this->switchTo(stateID);
    return *this;
}

StateMachine& StateMachine::operator+=(const std::shared_ptr<State>& s) {
    auto it = states.insert(std::make_pair(currentStateID, s));
    it.first->second->onCreate();
    currentStateID++;
    return *this;
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
    auto it = states.insert(std::make_pair(currentStateID, state));
    it.first->second->onCreate();

    return currentStateID++;
}

void StateMachine::erase(int stateID) {
    auto it = states.find(stateID);
    if (it != std::end(states)) {
        if (currentState == it->second) {
            currentState = nullptr;
            ///* todo: investigate if its buggy */
        }

        it->second->onDestroy();

        --currentStateID;
        states.erase(it);
    } else {
        std::cerr << "Cannot erase StateID: " << stateID << std::endl;
        ///* todo: throw EraseStateBadID */
    }
}
