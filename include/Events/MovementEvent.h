#pragma once

#include <Entities/Block.h>
#include "Entities/Player/Player.h"


class MovementEvent {
public:
    MovementEvent(Player& player, std::vector<std::unique_ptr<Entity>>& blocks);

    MovementEvent(const MovementEvent&) = delete;
    MovementEvent& operator=(const MovementEvent&) = delete;

    void updateAxisX(float dt);
    void updateAxisY(float dt);

private:
    Player& player;
    std::vector<std::unique_ptr<Entity>>& blocks;
};

