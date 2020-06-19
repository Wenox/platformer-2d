/** @file */
#pragma once



#include <SFML/Graphics.hpp>

/** \class MissingFont
 *
 *  \ingroup groupEntities
 *
 *  \brief Custom exception class. */

class MissingFont : public std::exception {
    std::string msg;
public:
    /** Constructor with default parameter value. */
    MissingFont(std::string msg = "Missing font") : msg(std::move(msg)) {}

    /** Overriden what() method. */
    virtual const char* what() const noexcept override {
        return msg.c_str();
    }
};

/** \class FpsOverlay
 *
 *  \ingroup groupEntities
 *
 *  \brief Prints the Fps to the screen.
 *
 *  \note Fps can be turned off and on by game player at any time during run-time.
 *
 *  Updated every game frame.
 *
 *
 *  */
class FpsOverlay : public sf::Drawable {
public:
    /** \brief Constructs an FpsOverlay. Calls setFont() and setFps().
    *
     * \warning May throw.
     *
    * */
    FpsOverlay();

    /** \brief Draw method used to render #fps onto the window.
     * @param target Window for the #fps to be rendered onto.
     * @param states Optional render states
     *
     * Overrides Entity draw method.
     *
     * \note Passing states is optional.
     * */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    /** Update the displayed number of #fps based on time elapsed since previous frame.
     *
     * @param dt Time elapsed since previous frame. */
    void update(float dt);

private:
    sf::Font font; ///< Font used to initialize the text.
    sf::Text fps; ///< Fps text number drawn to the screen in left-bottom corner.

    /** Calculate current Fps based on time elapsed since previous frame.
     *
     * @returns std::string number of Fps expressed as a std::string for a convenience.
     * */
    std::string calcCurrentFps(float dt);

    /** \brief Sets #font to customizable ::config::widgetsFontName.
     *
     * \warning May throw. */
    void setFont();

    /** \brief Sets the #fps using the #font and text configurations. */
    void setFps();
};


