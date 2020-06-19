/** @file */

#pragma once

#include "Entity.h"


/** \class HeartCollectible
 *
 *  \ingroup groupEntities
 *
 *  \brief Used to represent the collectible hearts (player lives).
 *
 *  \note A concrete Entity class overriding the draw method.
 *
 * */
class HeartCollectible : public Entity {
private:
    bool collected = false; ///< \brief True if HeartCollectible was collected.

public:
    /** \brief Constructs a HeartCollectible.
     * @param position initial position
     * */
    explicit HeartCollectible(sf::Vector2f position);

    /** \brief Draw method used to render #sprite onto the window.
     * @param target Window for the sprite to be rendered onto.
     * @param states Optional render states
     *
     * Overrides Entity draw method.
     *
     * \note Passing states is optional.
     * */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    /** Checks if the heart was already #collected.
     * @returns Was the heart already #collected?
     * */
    bool wasCollected() const;

    /** Sets the #collected status to a new one.
     *
     * @param status new #collected status*/
    void setCollected(bool status);
};


