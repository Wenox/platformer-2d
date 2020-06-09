#pragma once

#include "Player.h"
#include <cmath>
#include <Entities/Block.h>

class CollisionEvent {
public:
    CollisionEvent(Player& player, std::vector<std::unique_ptr<Entity>>& blocks);

    CollisionEvent(const CollisionEvent&) = delete;
    CollisionEvent& operator=(const CollisionEvent&) = delete;

    void updateAxisX();
    void updateAxisY();

    void handleCollision(const Entity& block, const std::function<void(const Entity&)>& resolveCollision);

    bool playerInRangeOf(const Entity& entity) const;
    bool playerIntersects(const Entity& entity) const;

    void resolveCollisionAxisX(const Entity& block);
    void resolveCollisionAxisY(const Entity &block);

private:
    Player& player;
    std::vector<std::unique_ptr<Entity>>& blocks;

    float collidableRange;
};
