#include <Consts.h>
#include "MovementEvent.h"

MovementEvent::MovementEvent(Player& player, std::vector<std::unique_ptr<Entity>>& blocks)
        :player{player},
         blocks{blocks},
         velX{player.getVelocityX()}
{
}

void MovementEvent::updateAxisX(float dt) {
    switch (player.movingState) {
        case MovingState::standing:
            break;
        case MovingState::movingLeft:
            player.move({-velX * dt, 0});
            break;
        case MovingState::movingRight:
            player.move({velX * dt, 0});
            break;
        default:
            break;
    }
}

void MovementEvent::updateAxisY(float dt) {
    switch (player.jumpingState) {
        case JumpingState::onGround:
            if (!player.isDetectingGround(blocks)) {
                player.jumpingState = JumpingState::gravity;
            }
            break;
        case JumpingState::jumping:
            player.jumpFrame(dt);
            break;
        case JumpingState::gravity:
            player.gravityFrame(dt);
            break;
    }
}