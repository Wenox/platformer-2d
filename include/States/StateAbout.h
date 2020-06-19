/** @file */
#pragma once

#include "ResourceManager.h"
#include "StateMachine.h"
#include "StateID.h"

/** \class StateAbout
 *
 *  \ingroup theStates
 *
 *  \brief Encapsulates the logic of about menu within one StateAbout class. Displays the about texture.
 *
 *  \note The only possible transition from StateAbout is:
 *    - StateMenu
 *
 *
 *  Inherits from State base.
 *  Created inside Game and Stored inside StateMachine.
 *  Tbe ID of StateMenu can be retrieved from state::menuID.
 *
 * */
class StateAbout : public State {
public:
    /** \brief Create the StateAbout.
    *
    * @param stateMachine
    * @param resourceManager
    *
    * \brief Constructor invoked from Game.
    */

    StateAbout(StateMachine& stateMachine, ResourceManager& resources);

    /** \brief Processes all inputs received by #gui. */
    void processInput() override;
    /** \brief Draws the #gui onto the screen. */
    void draw(Window& window) override;

private:
    StateMachine& stateMachine;
    sf::Sprite aboutInfo;
};


