/** @file */

#pragma once

#include "Entity.h"

/** \class Objective
 *
 *  \ingroup groupEntities
 *
 *  \brief Used to represent the game Objective. Player intersecting Objective wins the game.
 *
 *  \note Can the Player find the Objective?
 *
 *  A concrete Entity class overriding the draw method.
 *
 * */
class Objective : public Entity {
public:

    /** \brief Constructs an Objective.
    * @param position initial position, defaulted to zero.
    *
    * */
    explicit Objective(sf::Vector2f position = {0, 0});

    /** \brief Draw method used to render #sprite onto the window.
     * @param target Window for the sprite to be rendered onto.
     * @param states Optional render states
     *
     * Overrides Entity draw method.
     *
     * \note Passing states is optional.
     * */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
