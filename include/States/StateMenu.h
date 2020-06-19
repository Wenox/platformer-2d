/** @file */

/** @defgroup theStates States
 *  Drawable game objects, drawn inside StateGame.
 *  @{
 */


/** @} */ // end of group1

#pragma once

#include "StateGame.h"
#include "MenuView.h"

/** \class StateMenu
 *
 *  \ingroup theStates
 *
 *  \brief Encapsulates the logic of main menu within one StateRestart class.
 *
 *  \note All possible transitions from StateMenu are:
 *    - StateGame
 *    - StateMapLoader
 *    - StateOptions
 *    - StateAbout
 *
 *  Inherits from State base.
 *  Created inside Game and Stored inside StateMachine.
 *  Tbe ID of StateMenu can be retrieved from state::menuID.
 *
 * */
class StateMenu : public State {
public:
    /** \brief Create the StateMenu.
     *
     * @param stateMachine
     * @param window
     * @param resourceManager
     *
     * \details
     * Sets the default #onHoverSound. Constructor invoked from Game.*/
    StateMenu(StateMachine& stateMachine, Window& window, ResourceManager& resourceManager);

    /** \brief Called when the StateMenu is created. Connects signals to gui widgets.
     *
     */
    void onCreate() override;

    /** \brief Called when StateMenu is activated. Updates the sound volume. */
    void onActivate() override;

    /** \brief Called when StateMenu is closed. Stores that previous state was state::menuID.*/
    void onDeactivate() override;

    /** \brief Processes all inputs received by #gui.
     *
     */
    void processInput() override;
    /** \brief Draws the #gui onto the screen. */
    void draw(Window&) override;

private:
    StateMachine& stateMachine;
    Window& window;
    ResourceManager& resources;

    MenuView gui;
    sf::Sound onHoverBtnSound;

    std::optional<std::variant<MapLoader<Bmp>, MapLoader<Txt>>> mapLoader;

    /** \brief Updates the buttons hover volume. */
    void updateHoverSoundVolume();
};


