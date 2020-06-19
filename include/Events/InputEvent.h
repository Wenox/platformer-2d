/** @file */

#pragma once

#include <Window.h>
#include <ActionMap.h>
#include "Player.h"
#include "ResourceManager.h"
#include "Event.h"

/** \class InputEvent
 *
 *  \ingroup theEvents
 *
 *  \brief Handles the user input within StateGame class. Uses ActionMap.
 *
 *
 *
 *  */
class InputEvent : public Event {
public:
    /** \brief Create an InputEvent instance.
     *
     * @param player player controller
     * @param resources the resources container
     * @param window
     *
     * \note Populates the #keys with default-set user keybindings.
     *  */
    explicit InputEvent(Player& player, ResourceManager& resources, Window& window);

    /** \brief Delete copy operations. */
    InputEvent(const InputEvent&) = delete;
    /** \brief Delete copy operations. */
    InputEvent& operator=(const InputEvent&) = delete;

    /** \brief Updates horizontal and vertical input events. */
    void update() override;

    static bool isPressed(sf::Keyboard::Key myKeyCode);
private:
    std::unordered_map<std::string, sf::Keyboard::Key> keys;
    ActionMap& actions = ActionMap::Instance();

    /** \brief Updates Horizontal events.
     *
     *  Horizontal actions:
     *    - Running Left
     *    - Running Right
     *    - Standing
     *
     *  Update the Player texture accordingly.
     *    */
    void updateHorizontal();

    /** \brief Update Vertical events.
     *
     * Checks if a Player is standing on the ground, and only then checks if Player tries to jump.*/
    void updateVertical();

    Player& player;
    ResourceManager& resources;
    Window& window;
};


