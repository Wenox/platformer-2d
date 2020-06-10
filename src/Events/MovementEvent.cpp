#include <Consts.h>
#include "MovementEvent.h"

MovementEvent::MovementEvent(Player& player, std::vector<std::unique_ptr<Entity>>& blocks)
        :player{player},
         blocks{blocks}
{
}

void MovementEvent::updateAxisX(float dt) {
    switch (player.movingState) {
        case MovingState::standing:
            break;
        case MovingState::movingLeft:
            player.move({- player.getVelocity() * dt, 0});
            break;
        case MovingState::movingRight:
            player.move({player.getVelocity() * dt, 0}); /** todo: dont use getter, just bind velocity to const */
            break;
        default:
            break;
    }
}

void MovementEvent::updateAxisY(float dt) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        player.move({0, - player.getVelocity() * dt});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        player.move({0, player.getVelocity() * dt});
    }
}