/** @file */

#pragma once

#include <array>
#include "Life.h"
#include "LivesBorder.h"

/** \class LivesOverlay
 *
 *  \ingroup groupEntities
 *
 *  \brief Encapsulates player lives overlay.
 *
 *  \note This class is relevant only in StateGame.
 *
 *  */
class LivesOverlay : public sf::Drawable {
public:
    /** \brief Constructs a LivesOverlay.
    * @param renderWindow for settings the view
     * @param textures reference to container with Heart and HeartEmpty textures (among others)
    *
    * */
    explicit LivesOverlay(sf::RenderWindow& renderWindow, ResourceHolder<res::Texture, sf::Texture>& textures);
/** \brief Draw method used to render #fps onto the window.
     * @param target Window for the #fps to be rendered onto.
     * @param states Optional render states
     *
     * Overrides Entity draw method.
     *
     * \note Passing states is optional.
     * */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    /** \brief Decrease player life by one. */
    void decreaseLife() {
        availableLives -= 1;
        lives[availableLives].kill();
    }

    /** \brief Increase player life by one. */
    void increaseLife() {
        lives[availableLives].revive();
        availableLives += 1;
    }

    /** \brief Refill all player lives. */
    void refillLives() {
        while (!this->hasAllLives()) {
            this->increaseLife();
        }
    }


    /** \brief Checks if Player has all lives remaining.
     *
     * @returns does Player have all lives? */
    bool hasAllLives() const {
        return availableLives >= lives::count;
    }

    /** \brief Checks if Player has no lives left and should be dead.
     *
     * \note Player should be dead if #availableLives are non-positive.
     * @returns Is Player dead? */
    bool isDead() const {
        return availableLives <= 0;
    }

    /** \brief Gets the number of available lives remaining.
     *
     * @returns A number of player available lives remaining.  */
    int getAvailableLives() const { return availableLives; }

    /** \brief Checks if Player has any lives available.
     * @returns Does the Player have any lives available? */
    bool livesAvailable() const { return availableLives > 0; }

private:
    sf::RenderWindow& renderWindow; ///< Handles the view.

    std::array<Life, lives::count> lives; ///< Static array of Player lives.
    LivesBorder border; ///< Border wrapped around Player lives.
    sf::View HUD; ///< Needed for setting the view by #renderWindow.

    int availableLives = lives::count; ///< Remaining lives.
};





