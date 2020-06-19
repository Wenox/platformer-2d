/** @file */

#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <queue>

/** \class Window
 *
 *  \ingroup Core
 *
 *  \brief Responsible for drawing onto the screen.
 *
 *  A fundamental class that encapsulates #window and its utilities.
 *
 *  \note Game execution ends once the #window is closed by calling close() method.
 *
 * */
class Window {
public:

    /** \brief Constructs a Window with a given windowName.
     *
     * Sets framerate limit to config::maxFps and ::config::maxFps and ::maxFps and #maxFps and ::config#maxFps and #config::maxFps and #config#maxFps and  heh
     * calls setWindowIcon() which may throw if no icon image is found.
     *
     * When setWindowIcon() throws, the default operating system icon is loaded.
     *
     *
     * \note The game works in a **frame-rate independent way** which means that the game works correctly in 10, 60 or 3000 FPS.
     *
     * \note This game works in 3000 FPS on my slow computer when the maps are small. :-)
     * */
    explicit Window(std::string_view windowName);

    /** \brief Updates the window events.
     *
     *  Inserts all gathered events since previous frame into #events queue and checks if the user tried closing the window.
     *
     *  \note A dedicated #queue is needed because there can be more than two windows within a frame, and handling them is
     *  fone in a a lower abstraction level classes.
     *
     * */
    void update();


    /** \brief Starts the drawing procedure.
     *
     * Effectively: clears the screen with a color.
     *
     * Called from Game draw() method.
     *
     * */
    void beginDraw();

    /** \brief Draws the drawable objects onto the screen.
     * @param drawable A valid drawable entity
     * Unlike beginDraw() and endDraw(), this method is called from StateMachine */
    void draw(const sf::Drawable& drawable);


    /** \brief Ends the drawing procedure.
     *
     * Effectively: displays the rendered #window.
     *
     * Called from Game draw() method.
     * */
    void endDraw();

    /** \brief Closes the #window.
     *
     * \warning Calling this method effectively means ending the <em>Game loop</em>, and hence finish the program.
     *
     * */
    void close();

    /** Check if #window is still opened.
     *
     * A condtion for ending the main game loop.
     *
     * @return Is window opened? */
    bool isOpen() const;

    /** Updates the #window view with a possibly new Camera view position.
     *
     * Called every frame. Called only inside StateGame.
     *
     * \note: Only a part of a World is displayed to the screen.
     *
     * @param view A new view of Camera class.
     * */
    void updateView(const sf::View& view);

    /** \brief Retrieve the #events queue.
     *
     * Called every frame by all classes having their own View gui instance.
     *
     * Ensures correct drawing behaviour of View gui instances.
     *
     * \note StateGame and StateAbout do not use View gui instance.
     *
     *
     *
     * */
    std::queue<sf::Event>& getEvent();

    /** Retrieve the #window.
     *
     * The retrieved #window is an instance of RenderTarget.
     *
     * */
    sf::RenderWindow& getWindow();

    /** Get the width of the #window.
     * @returns The window width.
     * */
    unsigned int getWidth()  const noexcept;
    /** Get the width of the #window.
     * @returns The window height.
     * */
    unsigned int getHeight() const noexcept;

private:
    sf::RenderWindow window; ///< At a lowest level, everything is drawn to this instance.
    std::queue<sf::Event> events; ///< Queue of Events cleaned up game every frame.

    /** Sets the application's window icon.
     *
     *  This method throws when no icon is found. In such a case default Operating System icon is set.
     * */
    void setWindowIcon();
};


