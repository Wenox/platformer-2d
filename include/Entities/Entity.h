/** @file */

/** @defgroup groupEntities Entities
 *  Drawable game objects, drawn inside StateGame.
 *  @{
 */


/** @} */ // end of group1



#pragma once

#include <SFML/Graphics.hpp>
#include "Resources.h"
#include "ResourceHolder.h"


/** \class Entity
 *
 *  \ingroup groupEntities
 *
 *  \brief A base drawable Entity class. All drawable entities (game objects) inherit from it.
 *
 *  Contains helper methods common to all entitie e.g. setting position, retrieving position.
 *
 *  Enables all move and copy operations (Rule of 5).
 *
 * */
class Entity : public sf::Drawable, public sf::Transformable {
public:

    /** \brief Draws the #sprite onto the target.
     * @param target Window for the sprite to be rendered onto.
     * @param states Optional render states
     *
     * Overrides pure virtual in sf::Drawable class.
     *
     * \note Passing states is optional.
     * */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    /** \brief Move the entity #sprite by a float vector.
     * @param offset move vector
     *
     * \note Offset is **added** to current sprite position.
     * */
    void move(const sf::Vector2f& offset);
    /** \brief Move the entity #sprite by a explicit float coordinates.
     * @param offsetX
     * @param offsetY
     *
     * \note Offset is **added** to current sprite position.
     * */
    void move(float offsetX, float offsetY);


    /** \brief Sets #sprite position.
     * @param position given by Vector2f */
    void setPosition(const sf::Vector2f& position);
    /** \brief Sets #sprite position.
     * @param position given by explicit coordinates. */
    void setPosition(int x, int y);

    /** \brief Retrieve global bounds of the #sprite.
     * @returns sf::FloatRect #sprite global bounds. */
    sf::FloatRect getGlobalBounds() const;

    /** \brief Retrieve #sprite itself.
     * @returns sf::Sprite& a reference to a #sprite. */
    sf::Sprite& getSprite();


    /** Retrieve a width of the #sprite.
     * @returns float #sprite width. */
    float width() const;
    /** Retrieve a height of the #sprite.
 * @returns float #sprite height. */
    float height() const;
    /** \brief Retrieve #sprite x coordinate.
     * @returns float #sprite x coordinate */
    float left() const;

    /** \brief Retrieve #sprite right side x coordinate.
     * @returns #sprite right side x coordinate */
    float right() const;

    /** \brief Retrieve #sprite y coordinate.
     * @returns float #sprite y coordinate */
    float top() const;

    /** \brief Retrieve #sprite bottom side y coordinate.
 * @returns #sprite bottom side y coordinate */
    float bot() const;

    /** \brief Rotate the sprite Left by 90 degrees. */
    void rotateLeft();

    /** \brief Rotate the sprite Right by 90 degrees. */

    void rotateRight();

    /** \brief Rotate the sprite by 180 degrees. */

    void rotateTop();

    /** \brief Enable default destructor. */
    virtual ~Entity() = default;
    /** \brief Enable default copy operations. */
    Entity(Entity const&) = default;
    /** \brief Enable default move operations. */
    Entity(Entity&&) noexcept = default;
    /** \brief  Enable default copy operations. */
    Entity& operator=(Entity const&) = default;
    /** \brief Enable default move operations. */
    Entity& operator=(Entity&&) noexcept = default;


protected:

    /** Creates an entity at a given position
     *
     * @param position starting Entity position
     *
     * \note Entity constructor is protected so only deriving classes can create it to be more meaningful. */
    explicit Entity(sf::Vector2f position);


    /** Creates an entity at a given position.
     * @param textureHolder textureHolder reference container
     * @param textureID ID of the texture to be set to Entity
     * @param position starting Entity position
     *
     * \note This construction uses sets default position to (0, 0)
     * \note Entity constructor is protected so only deriving classes can create it to be more meaningful. */
    Entity(ResourceHolder<res::Texture, sf::Texture>& textureHolder, res::Texture textureID, sf::Vector2f position);
    Entity(ResourceHolder<res::Texture, sf::Texture>& textureHolder, res::Texture textureID);

    sf::Sprite   sprite; ///< Entity sprite
    sf::Vector2f position;
};


