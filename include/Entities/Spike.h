/** @file */

#pragma once

#include "Encoder.h"
#include "Entity.h"


/** \class Spike
 *
 *  \ingroup groupEntities
 *
 *  \brief Used to represent the spikes. Intersecting spike kills the Player.
 *
 *  There are four different possible spike views:
 *    - left-oriented spike
 *    - right-oriented spike
 *    - top-oriented spike
 *    - bot-oriented spike
 *
 *  \note All of the above spike re-use the very same texture.
 *
 *  A concrete Entity class overriding the draw method.
 *
 * */
class Spike : public Entity {
public:

    /** \brief Constructs a Spike.
     * @param spikeType the facing direction of spike.
     * @param position initial position.
     *
     * */
    explicit Spike(Obj::Entity spikeType, sf::Vector2f position);

    /** \brief Draw method used to render #sprite onto the window.
     * @param target Window for the sprite to be rendered onto.
     * @param states Optional render states
     *
     * Overrides Entity draw method.
     *
     * \note Passing states is optional.
     * */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    Obj::Entity spikeType;

    /** \brief Sets the spike #sprite texture direction.
     *
     * Four possible directions:
     *   - SpikeLeft
     *   - SpikeRight
     *   - SpikeTop
     *   - SpikeBot
     *
     * The direction is set by rotating #sprite.
     *
     * */
    void setTextureDirection();
};


