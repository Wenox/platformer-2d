/** @file */
#pragma once

#include <SFML/Audio/Sound.hpp>
#include "ResourceManager.h"
#include "KeybindsView.h"
#include "Action.h"
#include "ActionMap.h"
#include "StateMachine.h"


/** \class StateKeybinds
 *
 *  \ingroup theStates
 *
 *  \brief Encapsulates the logic of rebinding menu within one StateKeybinds class.
 *
 *  \note All possible transitions from StateMenu are:
 *    - StateOptions
 *
 *  Inherits from State base.
 *  Created inside Game and Stored inside StateMachine.
 *  Tbe ID of StateMenu can be retrieved from state::menuID.
 *
 * */
class StateKeybinds : public State {
private:
    Action action;

public:
    /** \brief Create the StateKeybinds.
    *
    * @param stateMachine
    * @param window
    * @param resourceManager
    *
    * \details
    * Sets the default #onHoverSound. Constructor invoked from Game. */
    StateKeybinds(StateMachine& stateMachine, Window& window, ResourceManager& resourceManager);

    /** \brief Called when the StateKeybinds is created. Connects signals to gui widgets. */
    void onCreate() override;
    /** \brief Called when StateKeybinds is activated. Updates the sound volume. */
    void onActivate() override;

    /** \brief Processes all inputs received by #gui.
     *
     * \note
     * Also, process keypresses events trying to go back to StateOptions.
     *
     */
    void processInput() override;

    /* \brief Show registering key animations and update the #actionMap keybinds. */
    void update(float dt) override;
    /** \brief Draws the #gui onto the screen. */
    void draw(Window&) override;

private:
    StateMachine& stateMachine;
    Window& window;

    ActionMap& actionMap = ActionMap::Instance();

    KeybindsView gui;

    sf::Sound onHoverBtnSound;
    /** \brief Updates the buttons hover volume. */
    void updateHoverSoundVolume();
};
