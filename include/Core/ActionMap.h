#pragma once

/** @file */

#include <SFML/Window/Keyboard.hpp>
#include <unordered_map>
#include <string>

/** \class Game
 *
 *  \ingroup Core
 *
 *  \brief Container for player actions keybinds.
 *
 *  Keybinds are held within #actionMap.
 *
 *  A given keybind can be bound to only one action,
 *  so binding an action to a previously existing keybind invalidates that previous action bind.
 *
 *  \note This is only one singleton class within this whole project; and having just one singleton in a non-trivial project is not necessarily considered harmful. My singleton implementation is **correctly-destroyed, lazy-evaluated, and thread-safe**.
 *
 *  * <em>\See <a href=" http://www.vincehuston.org/dp/singleton.html">Singleton design pattern</a>)</em>
 *
 * */
class ActionMap {
private:
    std::unordered_map<std::string, sf::Keyboard::Key> actionMap; ///< Map container for user keybinds. The default keybinds are set in a Configuration.h file.

public:
    /** \brief Insert {key, value} = {action, key} pair onto the map.
     *
     * @param action This is a map's key.
     * @param key    This is a map's value.
     *
     * \warning Distinguish between 'key' as a keybind and a 'key' as a general map's data structure key vocabulary.
     *
     * Here, an action is a <em>general</em> map key, while a key is a <em>general</em> map's value.
     * */
    void insert(const std::string& action, sf::Keyboard::Key key);

    /** \brief Update a given keybind.
     *
     *
     *
     * @param action An action to be bound onto...
     * @param key ...the given keybind.
     */
    void set(const std::string& action, sf::Keyboard::Key key);


    /** \brief Retrieve the #actionMap keybinds container.
     *
     * @returns Keybinds map container.
     *
     * */
    auto& getActionMap() {
        return actionMap;
    }

    /** \brief Retrieve the size of the #actionMap keybinds container.
     *
     *  @returns The size of #actionMap keybinds container.
     * */
    auto getActionMapSize() const {
        return actionMap.size();
    }


    /** The default move operations are deleted as it is a singleton.
     *
     * \note Copy operations are implicitly deleted.
     *
     * <em>Scott Meyers: make the deleted operations public for better error messages.</em>
     * */
    ActionMap(ActionMap const&) noexcept = delete;
    /** The default move operations are deleted as it is a singleton.
     *
     * \note Copy operations are implicitly deleted.
     *
     * <em>Scott Meyers: make the deleted operations public for better error messages.</em>
     * */
    void operator=(ActionMap const&) noexcept = delete;

    ~ActionMap() = default;

    /** \brief Retrieve the singleton instance of ActionMap.
     *
     * \note My singleton implementation is **lazy-evaluated, correctly-destroyed, and thread-safe**.
     *
     *
     * */
    static ActionMap& Instance();

private:

    /** Prohibit*/
    ActionMap();
};


