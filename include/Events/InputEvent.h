#pragma once

#include <Window.h>
#include <ActionMap.h>
#include "Player.h"
#include "ResourceManager.h"
#include "Event.h"


class InputEvent : public Event {
public:
    explicit InputEvent(Player& player, ResourceManager& resources, Window& window);

    InputEvent(const InputEvent&) = delete;
    InputEvent& operator=(const InputEvent&) = delete;
    /** todo: ro5 */

    void update();

    static bool isPressed(sf::Keyboard::Key myKeyCode);
private:
    std::unordered_map<std::string, sf::Keyboard::Key> keys;
    ActionMap& actions = ActionMap::Instance();

    void updateHorizontal();
    void updateVertical();

    Player& player;
    ResourceManager& resources;
    Window& window;
};


