/** @file */
#pragma once

#include <SFML/Audio/Sound.hpp>
#include "ResourceManager.h"
#include "MapLoaderView.h"
#include "MapLoader.h"
#include "StateMachine.h"


/** \class StateMapLoader
 *
 *  \ingroup theStates
 *
 *  \brief Encapsulates the logic of map loader menu within one StateMapLoader class.
 *
 *  \note All possible transitions from StateMapLoader are:
 *    - StateGame
 *    - StateMenu
 *
 *  Inherits from State base.
 *  Created inside Game and Stored inside StateMachine.
 *  Tbe ID of StateMenu can be retrieved from state::menuID.
 *
 * */
class StateMapLoader : public State {
public:
    /** \brief Create the StateMapLoader.
    *
    * @param stateMachine
    * @param window
    * @param resourceManager
    *
    * \details
    * Sets the default #onHoverSound. Constructor invoked from Game.*/
    StateMapLoader(StateMachine& stateMachine, Window& window, ResourceManager& resourceManager);

    /** \brief Called when the StateMapLoader is created. Connects signals to gui widgets. */
    void onCreate() override;
    /** \brief Called when StateMapLoader is activated. Hide badMapLabel and update the sound volume.
     *
     * Possibly the user was in StateMapLoader earlier on, entered wrong map name and went back to StateMenu.
     * Therefore: we need to hide badMapLabel message upon re-entering StateMapLoader.
     *
     * */
    void onActivate() override;

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

    MapLoaderView gui;

    std::optional<std::variant<MapLoader<Bmp>, MapLoader<Txt>>> mapLoader;

    sf::Sound onHoverBtnSound;

    /** \brief Updates the buttons hover volume. */
    void updateHoverSoundVolume();

    void setMapLoaderButton();
    void createGameFrom(std::string_view mapName);

    static void printHelp(std::ostream& ost);
};
