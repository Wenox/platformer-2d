/** @file */

#pragma once

#include "Player.h"
#include "Block.h"
#include "PhysicsEvent.h"

/** \class CollisionEvent
 *
 *  \ingroup theEvents
 *
 *  \brief CollisionEvent class responsible for solves player<->collidable collisions in **axis-independent way**.
 *
 *  \note
 *
 *  My general collision solving idea:
 *    - 1. Move player on X axis
 *    - 2. Check for collision
 *    - 3. Resolve that collision (move back the player on Y axis as little as possible, but so that he no longer collides)
 *    - 4. Move player on Y axis
 *    - 5. Check for collision
 *    - 6. Resolve that collision (ove back the player on Y axis as little as possible, but so that he no longer collides)
 *
 *  This collision algorithm was tested heavily and should never disappoint in such game, unless the player is passing-through entities due to very slow Fps, absurd high velocity, or both.
 *  This is never a case in my game as it runs in 300-3000 FPS (depending on the map size) on my <em>slow</em> laptop (assuming Fps limiter is unlocked).
 *
 *  Problem would rise at around or below 10 Fps, or <em>teleporting</em> velocity.
 *
 *  Alternatives are e.g. <em>Sweep and prune</em> algorithm, or raycasting.
 *
 *  \note Implements pure virtual methods from base PhysicsEvent class.
 *  */
class CollisionEvent : public PhysicsEvent {
public:
    /** \brief Create a CollisionEvent instance.
     *
     * @param player - controller
     * @param blocks - entities for the controller to be matched collisions against */
    CollisionEvent(Player& player, std::vector<std::unique_ptr<Entity>>& blocks);

    /** \brief Delete copy operations. */
    CollisionEvent(const CollisionEvent&) = delete;
    /** \brief Delete copy operations. */
    CollisionEvent& operator=(const CollisionEvent&) = delete;

    /** \brief Handle horizontal collisions.
     *
     *  Implements PhysicsEvent pure virtual method.
     */
    void updateAxisX(float) override;
    /** \brief Handle vertical collisions.
     *
     *  Implements PhysicsEvent pure virtual method.
     */
    void updateAxisY(float) override;

    /** \brief Axis-independent collision handler, invokes collision resolver.
     *
     * @param block Collidable entity player is matched against.
     * @param resolveCollision will be passed either resolveCollisionAxisX, or resolveCollisionAxisY
     * \note Collision is tried to be resolved only if:
     *   - player is in range of block (checked first)
     *   - player intersects a block   (checked if the above was true)
     *
     *
     *   */
    void handleCollision(const Entity& block, const std::function<void(const Entity&)>& resolveCollision);

    /** \brief Checks if Player is in range of a given entity.
     *
     * @param entity entity to be checked against.
     * @returns Was the Player in range of that entity?
     * */
    bool playerInRangeOf(const Entity& entity) const;
    /** \brief Checks if Player intersects a given entity.
     *
     * @param entity entity to be checked against.
     * @returns Was the player intersecting that entity?
     * */
    bool playerIntersects(const Entity& entity) const;


    /** \brief Solve the collision on X axis. Passed as an argument to std::function.
     *
     * @param block A block collision is resolved against. Needed to compute resolved Player position. */
    void resolveCollisionAxisX(const Entity& block);
    /** \brief Solve the collision on X axis. Passed as an argument to std::function.
     *
     * @param block A block collision is resolved against. Needed to compute resolved Player position.*/
    void resolveCollisionAxisY(const Entity &block);

private:
    Player& player; ///< Controller.
    std::vector<std::unique_ptr<Entity>>& blocks; ///< Collidable blocks.

    float collidableRange; ///< The entities do not have to be squares; in such a casae, collidableRange is the longer dimension.
};
