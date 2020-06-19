/** @file */


#pragma once

/** \enum Action
 *
 *  \ingroup Core
 *
 *  \brief An enum containing available game actions taken by the player during the game.
 *
 *  The default action keybinds are:
 *   - **W** for jumping
 *   - **A** for moving left
 *   - **D** for moving right
 *
 *  \note An action can be rebound to a different key inside StateKeybinds.
 */
enum class Action {
    Jump,
    GoLeft,
    GoRight,
    NONE
};