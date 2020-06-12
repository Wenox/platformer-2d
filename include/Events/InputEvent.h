#pragma once

#include "Player.h"
#include "ResourceManager.h"


class InputEvent : public Player {
public:
    explicit InputEvent(Player& player, ResourceManager& resources);

    InputEvent(const InputEvent&) = delete;
    InputEvent& operator=(const InputEvent&) = delete;
    /** todo: ro5 */

    void update();

private:
    void updateHorizontal();
    void updateVertical();

    Player& player;
    ResourceManager& resources;
};


