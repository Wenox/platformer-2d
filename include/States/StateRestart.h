/** @file */
#pragma once

#include "StateMachine.h"
#include "RestartView.h"


/** \class StateRestart
 *
 *  \ingroup theStates
 *
 *  \brief Encapsulates the logic of restart menu within one StateRestart class.
 *
 *  \note All possible transitions from StateMenu are:
 *    - StateGame
 *    - StateMenu
 *
 *  Inherits from State base.
 *  Created inside Game and Stored inside StateMachine.
 *  Tbe ID of StateMenu can be retrieved from state::menuID.
 *
 * */
class StateRestart : public State {
public:
    /** \brief Create the StateRestart.
     *
     * @param stateMachine
     * @param window
     * @param resourceManager
.*/
    StateRestart(StateMachine& stateMachine, Window& window, ResourceManager& resourceManager);

    /** \brief Called when the StateRestart is created. Connects signals to gui widgets. */
    void onCreate() override;

    /** \brief Sets either gameWonTexture() or gameLostTexture(). */
    void onActivate() override;

    /** \brief Stores the state::restartID as #previousStateID. */
    void onDeactivate() override;

    /** \brief Processes all inputs received by #gui. */
    void processInput() override;

    /** \brief Draws the #gui onto the screen. */
    void draw(Window&) override;

private:
    StateMachine& stateMachine;
    Window& window;

    RestartView gui;
};