#pragma once

#include "Player.h"
#include "Block.h"
#include "PhysicsEvent.h"


class MovementEvent : public PhysicsEvent {
public:
    MovementEvent(Player& player, std::vector<std::unique_ptr<Entity>>& blocks);

    MovementEvent(const MovementEvent&) = delete;
    MovementEvent& operator=(const MovementEvent&) = delete;

    void updateAxisX(float dt) override;
    void updateAxisY(float dt) override;

private:
    Player& player;
    std::vector<std::unique_ptr<Entity>>& blocks;

    const float velX;
};

