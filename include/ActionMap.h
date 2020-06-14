#pragma once

#include <SFML/Window/Keyboard.hpp>
#include <unordered_map>
#include <string>
#include <stdexcept>
#include <mutex>


class ActionMap {
private:
    std::unordered_map<std::string, sf::Keyboard::Key> actionMap;

public:
    void insert(const std::string& action, sf::Keyboard::Key key);
    void set(const std::string& action, sf::Keyboard::Key key);


    auto& getActionMap() {
        return actionMap;
    }

    auto getActionMapSize() const {
        return actionMap.size();
    }

    ActionMap(ActionMap const&) = delete;
    void operator=(ActionMap const&) = delete;
    static ActionMap* Instance();

protected:
    ActionMap();
    ~ActionMap() = default;

private:
    static std::mutex constructionGuard;
    static ActionMap* instance;
};


