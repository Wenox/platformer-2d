/** @file */

#pragma once

#include "Entity.h"


/** \class Life
 *
 *  \ingroup groupEntities
 *
 *  \brief Used to represent the player life overlay **item** as a hearts in corner of the screen(player lives).
 *
 *
 *  \note Do not confuse an Overlay heart with HeartCollectible (game object).
 *
 *  A concrete Entity class overriding the draw method.
 *
 *  \note #aliveTexture is displayed when Life is available (<em>red</em> heart), while #deadTexture is displayed when life is gone (<em>red-gray</em> heart).
 *
 * */
class Life : public Entity {
    bool lifeAvailable = true; ///< \brief Is this Player life available?

    sf::Texture* aliveTexture{}; ///< \brief Simply binds to an already exisitng aliveTexture.
    sf::Texture* deadTexture{}; ///< \brief Simply binds to an already existing deadTexture.
public:
    /** \brief Constructs a Life.
    * @param position initial position, defaulted to zero.
    *
    * */
    explicit Life(sf::Vector2f position = {0, 0});

    /** \brief Draw method used to render #sprite onto the window.
     * @param target Window for the sprite to be rendered onto.
     * @param states Optional render states
     *
     * Overrides Entity draw method.
     *
     * \note Passing states is optional.
     * */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    /** \brief Is this player Life available?
     * @returns Is this player life available? */
    bool isAvailable() const { return lifeAvailable; }

    /** \brief Removes the life.
     *
     * #lifeAvailable is set to false and #sprite is set to #deadTexture
     * */
    void kill() {
        lifeAvailable = false;
        this->getSprite().setTexture(*deadTexture);
    }

    /** \brief Regain the life.
     *
     * #lifeAvailable is set to true and #sprite is set to #aliveTexture
     * */
    void revive() {
        lifeAvailable = true;
        this->getSprite().setTexture(*aliveTexture);
    }

    /** \brief Stores #aliveTexture by binding a pointer to an already existing texture reference.
     *
     * @param texture #aliveTexture is bound to this parameter
     *
     * */
    void storeAliveTexture(sf::Texture& texture) {
        aliveTexture = &texture;
    }
/** \brief Stores #deadTexture by binding a pointer to an already existing texture reference.
     *
     * @param texture #deadTexture is bound to this parameter
     *
     * */
    void storeDeadTexture(sf::Texture& texture) {
        deadTexture = &texture;
    }

    /** Retrieves the reference to an #aliveTexture# by dereferencing it.
     *
     * @returns sf::Texture& reference to aliveTexture */
    sf::Texture& getAliveTexture() const {
        return *aliveTexture;
    }

    /** Retrieves the reference to a #deadTexture by dereferencing it.
     *
     * @returns sf::Texture& reference to #deadTexture */
    sf::Texture& getDeadTexture() const {
        return *deadTexture;
    }

};


