/** @file */
#pragma once

#include <SFML/Audio/Sound.hpp>
#include "OptionsView.h"
#include "ResourceManager.h"
#include "StateMachine.h"

/** \class StateOptions
 *
 *  \ingroup theStates
 *
 *  \brief Encapsulates the logic of options menu within one StateOptions class.
 *
 *  \note All possible transitions from StateMenu are:
 *    - StateGame
 *    - StateMenu
 *    - StateKeybinds
 *    - StatePaused
 *
 *
 *  Inherits from State base.
 *  Created inside Game and Stored inside StateMachine.
 *  Tbe ID of StateMenu can be retrieved from state::menuID.
 *
 * */
class StateOptions : public State {
public:
    /** \brief Create the StateOptions.
    *
    * @param stateMachine
    * @param window
    * @param resourceManager
    *
    * \details
    * Sets the default #onHoverSound and #corners textures and positions. Constructor invoked from Game.*/
    StateOptions(StateMachine& stateMachine, Window& window, ResourceManager& resources);

    /** \brief Called when the StateOptions is created. Connects signals to gui widgets. */
    void onCreate() override;

    /** \brief Processes all inputs received by #gui.
     *
     * \note
     * Also, process keypresses events trying to switch to a **previous** State.
     *
     */
    void processInput() override;
    /** \brief Draws the #gui and #corners onto the screen. */
    void draw(Window&) override;

private:
    StateMachine& stateMachine;
    Window& window;

    OptionsView gui;

    std::array<std::reference_wrapper<sf::Texture>, 4> cornersTextures;
    std::array<sf::Sprite, 4> corners;

    sf::Sound onHoverBtnSound;
    /** \brief Updates the buttons hover volume. */
    void updateHoverSoundVolume();

    /** Saves configuration options into struct. */
    void saveOptions();
    /** Updates slider appearence view based on Sound Enable checkbox. */
    void updateSlider();
};


