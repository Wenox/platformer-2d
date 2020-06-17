#include "ActionMap.h"


ActionMap::ActionMap() {
    this->insert("GoLeft",  sf::Keyboard::A);
    this->insert("GoRight", sf::Keyboard::D);
    this->insert("Jump" ,   sf::Keyboard::W);
}

void ActionMap::insert(const std::string& action, sf::Keyboard::Key key) {
    actionMap.insert(std::make_pair(action, key));
}

void ActionMap::set(const std::string& action, sf::Keyboard::Key key) {
    auto it = actionMap.find(action);
    if (it != std::end(actionMap)) {
        it->second = key;
    } else {
        throw std::runtime_error("No such action: " + action);
    }
}


ActionMap& ActionMap::Instance() {
    static ActionMap instance;
    return instance;
}