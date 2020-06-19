#pragma once

/** @file */

#include <variant>
#include "Entity.h"
#include "Overload.h"


/** \class Camera
 *
 *  \ingroup Core
 *
 *  \brief Responsible for viewing only a sensible, displayable part of the World to the screen. Handles all Camera collisions.
 *
 *  Camera is bound to the Player (sprite) position, **Player** is controller, but it can be rebound to any Entity (sprite) controller.
 *
 *  Camera's view width and height is equal to the Window width and height.
 *
 *  \note Camera can collide with the World borders **in a few different ways**.
 *
 *  **Possible collision types seen from a <em>user's<em> perspective:**
 *    - none
 *    - left
 *    - right
 *    - bottom
 *    - top
 *    - **left-top** corner
 *    - **left-bottom** corner
 *    - **right-top** corner
 *    - **right-bot** corner
 *
 *  **Real collision states at the implementation level:**
 *    - none
 *    - left
 *    - right
 *    - bottom
 *    - top
 *
 *  \warning
 *
 *  \note
 *
 *
 *  My Camera algorithm updates its position **on one axis at a time.**
 *
 *  **Algorithm:**
 *  - 1. Move Player (and Camera) on **X** axis.
 *  - 2. Check if camera is colliding on **X** axis? Store Left, Right or None accordingly.
 *  - 3. Calculate correct **X** position.
 *  - 4. Resolve that **X** collision based on whatever was previous **Y** collision state and calculated X position.
 *  - 5. **Store #solvedNow inside #previouslySolvedOtherAxis for **updateY()**.
 *
 *  - 6. Move Player (and Camera) on **Y** axis.
 *  - 7. Check if camera is colliding on **Y** axis?
 *  - 8. Calculate correct **Y** position.
 *  - 9. Resolve that **Y** collision, based on whatever was previous **X** collision state and calculated Y position.
 *  - 10. Store #solvedNow inside #previouslySolvedOtherAxis for **updateX()**.
 *
 *  \note Corollary: camera is not simultaneously colliding e.g. left-top. At the implementation level, it is only in one colliding state at a time.
 *
 * \warning Structs are used for std::variant (storing previously solved collision on the other axis), while Enum is used as a helper for storing current axis collision.
 *
 * */
class Camera {
private:
    struct None{}; /** \struct None
 * \ingroup Core
 * \brief Empty struct denoting there was previously None collision.
 *
 */

    struct Left{}; /** \struct Left
 * \ingroup Core
 * \brief Empty struct denoting previously solved on other axis was Left collision.
 *
 */
    struct Right{}; /** \struct Right
 * \ingroup Core
 * \brief Empty struct denoting previously solved on other axis was Right collision.
 *
 */

    struct Top{}; /** \struct Top
 * \ingroup Core
 * \brief Empty struct denoting previously solved on other axis was Top collision.
 *
 */

    struct Bot{}; /** \struct Bot
 * \ingroup Core
 * \brief Empty struct denoting previously solved on other axis was Bot collision.
 *
 */

    /** \enum CurrentCollision
     *
     *  \brief Enum holding state of the **currently solving** Collision found on the **same** axis.
     *
     *
     * */
    enum class CurrentCollision {
        None,
        Left,
        Right,
        Top,
        Bot
    };

    /** A camera can be only in one collision state at a time. */
    std::variant<None, Left, Right, Top, Bot> previouslySolvedOtherAxis{None{}}; ///< Holds solved collision from a previous, **different** axis, so proper response to corners-collision can be performed.
    CurrentCollision solvedNow{CurrentCollision::None}; ///< Whatever was just solved on the same axis.

    sf::View cameraView; ///< Viewable screen region drawn onto the window.

    sf::Sprite* controller{nullptr}; ///< Controlls the camera's position. Does **not** allocate dynamic memory.

public:
    /**
     * \brief Constructs a Camera from a Window's view.
     * @param view Window's view.
     *
     * Also sets relevant camera constants through setCamersConstants().
     * */
    explicit Camera(const sf::View& view) noexcept;

    /** \brief Updates the camera on **horizontal X** axis. Moves the camera and resolves the collision if needed.
     *
     * UpdateX knows if there was a Top, Bot or None collision in a previous frame **updateY()** call, because it was stored in #previouslySolvedOtherAxis.
     *
     * Therefore: updateX() can respond properly to corner collisions.
     *
     * \note Camera is colliding only on one axis at a time, even if it is "corner collision". */
    void updateX() noexcept;

    /** \brief Updates the camera on **vertical Y** axis. Moves the camera and resolves the collision if needed.
     *
     * UpdateY knows if there was a Left, Right or None collision in a previous frame **updateX()** call, because it was stored in #previouslySolvedOtherAxis.
     *
     * Therefore: updateY() can respond properly to corner collisions.
     *
     * \note Camera is colliding with only on one axis at a time, even if it is "corner collision". */
    void updateY() noexcept;

    /** \brief Update the #previouslySolvedOtherAxis variant state with whatever was just solved collision.
     *
     * \note This method is called on exit from updateX() or updateY(), so it can store the just solved collision.
     *
     * If exiting updateX() method, #previouslySolvedOtherAxis will be set to one of:
     *  - Left
     *  - Right
     *  - None
     * If exiting updateY() method, #previouslySolvedOtherAxis will be set to one of:
     *  - Top
     *  - Bot
     *  - None
     *
     *
     *
     *
     *
     *
 * \note Note that a #cameraView is always moving **on one axis at a time**.
 * */
    void storeJustSolvedForOtherAxis(CurrentCollision wasCollision) noexcept;

    /** \brief Detects if there is a collision on X axis as of **right now**.
     *
     *
     *  \note Right before calling this method, the Player controller (and hence: Camera view too!) was just moved on X axis.
     *
     *  If the collision was None (there is no collision), then X position was already correct.
     *  If the collision was Left, then correct X position is #leftBorderBoundary.
     *  If the collision was Right, then correct X position is #rightBorderBoundary.
     *
     *  \note Store Left, Right or None for the future **updateY()**
     *
     * @returns Correct (solved) collision-free X position.
     *  */
    float detectCollisionX() noexcept;

    /** \brief Detects if there is a collision on Y axis as of **right now**.
     *
     *
     *  \note Right before calling this method, the Player controller (and hence: Camera view too!) was just moved on Y axis.
     *
     *  If the collision was None (there is no collision), then Y position was already correct.
     *  If the collision was Top, then correct Y position is #topBorderBoundary.
     *  If the collision was Bot, then correct Y position is #bottomBorderBoundary.
     *
     *  \note Store Top, Bot or None for the future **updateX()** method (next game frame).
     *
     * @returns Correct (solved) collision-free Y position.
     *  */
    float detectCollisionY() noexcept;

    /** \brief Retrieve the #cameraView.
 *
 * @returns cameraView Displayed camera view.
 * */
    sf::View& getCameraView() noexcept;

    /** \brief Set the Entity that is controlling the Camera.
 *
 * @param controllingEntity the entity that will take control over #cameraView position/movement.
 *
 * On an implementation level, this simply binds to a sf::Sprite.
 *
 * \note In this game Player is controlling Camera, but any Entity could do.
 *
 *
 * */
    void setController(Entity& controllingEntity) noexcept;

private:
    float cameraWidth{}; ///< Camera width is same as Window width
    float cameraHeight{}; ///< Camera height is same as Window height
    float halvedCameraWidth{};
    float halvedCameraHeight{};

    float mapWidth{}; ///< For calculating #rightBorderBoundary.
    float mapHeight{}; ///< For calculating #bottomBorderBoundary.

    float leftBorderBoundary{}; ///< Precomputed solved X coord for Left collision.
    float rightBorderBoundary{}; ///< Precomputed solved X coord for Right collision.
    float topBorderBoundary{}; ///< Precomputed solved Y coord for Top collision.
    float bottomBorderBoundary{}; ///< Precomputed solved Y coord for Bot collision.

    float halvedSpriteWidth{};
    float halvedSpriteHeight{};

    /** \brief Store the Camera configuration constants. */
    void setCameraConstants() noexcept;

    /** \brief Store player's #halvedSpriteWidth and #halvedSpriteHeight.
     *
     * Stored so the camera is kept exactly in the center of the screen.
     *
     * */
    void setControllerConstants() noexcept;
};