#include <Consts.h>
#include "MovementEvent.h"

MovementEvent::MovementEvent(Player& player, std::vector<std::unique_ptr<Entity>>& blocks)
        :player{player},
         blocks{blocks}
{
}

void MovementEvent::updateAxisX(float dt) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        player.move({- player.getVelocity() * dt, 0});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        player.move({player.getVelocity() * dt, 0}); /** todo: dont use getter, just bind velocity to const */
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