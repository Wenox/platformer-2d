/** @file */

#pragma once

#include "Entity.h"


/** \class Block
 *
 *  \ingroup groupEntities
 *
 *  \brief Used to represent collidable game blocks.
 *
 *  Available collidable Block types:
 *    - BlockRed,
 *    - BlockBlue,
 *    - BlockBrown,
 *    - BlockGray,
 *    - BlockGreen,
 *    - BlockPurple,
 *    - BlockYellow,
 *    - BlockCrate,
 *    - Water1,
 *    - Water2,
 *    - Sign1,
 *    - Sign2,
 *
 * \see Obj::Entity
 *
 *  \note One specific texture e.g. BlockYellow is loaded only once to the memory.
 *
 * \note A concrete Entity class overriding the draw method.
 *
 * */
class Block : public Entity {
public:
    /** \brief Constructs a collidable Block.
    * @param position initial position, defaulted to zero.
    *
    * */
    explicit Block(sf::Vector2f position);

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


