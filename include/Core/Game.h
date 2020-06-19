/** \defgroup Core Core
 *
 *  \brief Classes that are core to the engine, yet don't belong in a dedicated package
 *
 *
 *  \defgroup Encoder Encoder
 *
 *  \brief Classes that are responsible for **encoding** the input file (Bmp or Txt) into complete game World.
 *
 *
 * */




/*! \mainpage My Personal Index Page
 *
 * \section intro Introduction
 *
 * This is the introduction.
 *
 * \section install Installation
 *
 * \subsection step1 Step 1: Opening the box
 *
 * etc...
 */

/** @file */

#pragma once

#include "ResourceManager.h"
#include "States/Core/StateMachine.h"
#include "Settings.h"


/** \class Game
 *
 *  \ingroup Core
 *
 *  \brief A fundamental class that runs the game loop. Invoked from main(), game execution starts and ends here.
 *
 * */

class Game {
public:
    /// Creates a Game.
    Game();

    /// Runs the game: called from main, this is where the main game loop starts.
    void run();

private:
    Window window; ///< The Window where the game is drawn.
    ResourceManager resources; ///< Contains persistent resources needed throughout game loop.
    StateMachine stateMachine; ///< Manages the game states <em>\See <a href="http://www.vincehuston.org/dp/state.html">State design pattern</a>)</em>


    sf::Clock clock; ///< Utility class that measures the elapsed time.
    float dt; ///< Time measured since previous game frame.

    /** @brief The function computes the time elapsed since the previous frame.
     *  The result is stored as seconds inside #dt variable <em>(float)</em>. */
    void computeDeltaTime();

    /** @brief Creates all game states but StateGame during Game construction time.
     *
     * Created states persist until the end of the game <em>(except for StateGame)</em>.
     *
     * A list of the available states:
     *   - StateAbout
     *   - StateGame
     *   - StateKeybinds
     *   - StateMapLoader
     *   - StateMenu
     *   - StateOptions
     *   - StatePaused
     *   - StateRestart
     *
     */
    void createStates();

    /** @brief Calls the StateMachine::processInput() method
     *
     * This method is continuously executed within a game loop.
     *
     * <em>\See <a href="http://www.vincehuston.org/dp/state.html">State design pattern</a>)</em>
     *
     * */
    void processInput();

    /** @brief Calls the StateMachine::update(float dt) and Window.update() methods.
     *
     * This method is continuously executed within a game loop.
     *
     * <em>\See <a href="http://www.vincehuston.org/dp/state.html">State design pattern</a>)</em>
     *
     * */
    void update();

    /** @brief Calls the StateMachine.draw() method
     *
     * This method is continuously executed within a game loop.
     *
     * <em>\See <a href="http://www.vincehuston.org/dp/state.html">State design pattern</a>)</em>
     *
     * */
    void draw();

    /** \brief Checks if a Game is still running.
     *
     *
     *
     *  Boolean condition for ending the game.
     *  \note A Game is running as long as a Window is being kept open.

     *  @returns Is the game still running?
     *
     *
     *
     *
     * */
    bool isRunning() const;

public:

    /** \brief Get the #window instance.
     *
     * @returns Reference to an instance of Window class.
     *
     * */
    Window& getWindow();

    /** \brief Get the #resources instance.
     * @returns Reference to an instance of ResourceManager class.
     * */
    ResourceManager& getResources();

    /** \brief Get the #stateMachine instance.
     *
     * @returns Reference to an instance of StateMachine.
     *
     * */
    StateMachine& getStateMachine();
};


