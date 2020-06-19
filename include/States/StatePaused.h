/** @file */
#pragma once

#include <SFML/Audio/Sound.hpp>
#include "PausedView.h"
#include "ResourceManager.h"
#include "StateMachine.h"
#include "StateID.h"


/** \class StatePaused
 *
 *  \ingroup theStates
 *
 *  \brief Encapsulates the logic of paused menu within one StatePaused class.
 *
 *  \note All possible transitions from StateMenu are:
 *    - StateGame
 *    - StateOptions
 *    - StateMenu
 *
 *  Inherits from State base.
 *  Created inside Game and Stored inside StateMachine.
 *  Tbe ID of StateMenu can be retrieved from state::menuID.
 *
 * */
class StatePaused : public State {
public:
    /** \brief Create the StatePaused.
    *
    * @param stateMachine
    * @param window
    * @param resourceManager
    *
    * \details
    * Sets the default #onHoverSound and #corners textures and positions. Constructor invoked from Game.*/
    StatePaused(StateMachine& stateMachine, Window& window, ResourceManager& resources);

    /** \brief Called when the StatePaused is created. Connects signals to gui widgets. */
    void onCreate() override;

    /** \brief Called when StatePaused is activated. Updates the view and the sound volume. */
    void onActivate() override;

    /** \brief Called when StatePaused is closed. Stores that previous state was state::pausedID.*/
    void onDeactivate() override;

    /** \brief Processes all inputs received by #gui.
     *
     * \note
     * Also, process keypresses events trying to switch to a different State.
     *
     */
    void processInput() override;
    /** \brief Draws the #gui onto the screen. */
    void draw(Window&) override;

private:
    StateMachine& stateMachine;
    Window& window;

    sf::View pausedView;

    PausedView gui;

    sf::Sound onHoverBtnSound;
};


