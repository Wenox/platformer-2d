/** @file */

#include <Configuration.h>
#include "CollisionEvent.h"


CollisionEvent::CollisionEvent(Player& player, std::vector<std::unique_ptr<Entity>>& blocks)
        :player{player},
         blocks{blocks},
         collidableRange{0.0f}
{
    /** Collidable entity does not have to be a square. In such a case, collidable range is the longer side */
    config::entityWidth == config::entityHeight ? collidableRange = config::entityWidth
                                                : collidableRange = std::max(config::entityWidth, config::entityHeight);
}

void CollisionEvent::updateAxisX(float) {
    for (auto& block : blocks) {
        handleCollision(*block, [this](const Entity &e) {
            this->resolveCollisionAxisX(e);
        });
    }
}

void CollisionEvent::updateAxisY(float) {
    for (auto& block : blocks) {
        handleCollision(*block, [this](const Entity &e) {
            this->resolveCollisionAxisY(e);
        });
    }
}

void CollisionEvent::handleCollision(const Entity& block, const std::function<void(const Entity&)>& resolveCollision) {
    if (playerInRangeOf(block) && playerIntersects(block)) {
        resolveCollision(block);
    }
}

bool CollisionEvent::playerInRangeOf(const Entity& entity) const {
    return std::abs(entity.left() - player.left()) < collidableRange
        && std::abs(entity.top()  - player.top())  < collidableRange;
}

bool CollisionEvent::playerIntersects(const Entity& entity) const {
    return entity.getGlobalBounds().intersects(player.getGlobalBounds());
}

void CollisionEvent::resolveCollisionAxisX(const Entity& block) {
    if (player.left() <= block.left()) { // collision from left
        player.move(-(player.right() - block.left()), 0);
    }
    else if (player.right() > block.left()) { // collision from right
        player.move(block.right() - player.left(), 0);
    }
    else {
        std::cerr << "Velocity on horizontal axis was too high\n";
        player.setToStartingPosition();
    }
}

void CollisionEvent::resolveCollisionAxisY(const Entity &block) {
    if (player.top() < block.top()) {        // collision from top
        player.move(0, -(player.bot() - block.top()));
        player.landOnGroundUpdate();
    } else if (player.bot() >= block.bot()) { // collision from bottom
        player.move(0, block.bot() - player.top());
        player.hitCeilingUpdate();
    } else {
        std::cerr << "Velocity on vertical axis was too high\n";
        player.setToStartingPosition();
    }
}