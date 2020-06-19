/** @file */

#pragma once

#include <SFML/Graphics.hpp>
#include "LivesOverlayConfig.h"


/** \class LivesBorder
 *
 *  \ingroup groupEntities
 *
 *  \brief A border around the LivesOverlay.
 *
 *  */
class LivesBorder : public sf::Drawable {
public:
    /** \brief Constructs a LivesBorder.
    * @param viewport viewport position will be bound to.
    *
    * */
    explicit LivesBorder(const sf::Rect<float>& viewport);
/** \brief Draw method used to render #border onto the window.
     * @param target Window for the #border to be rendered onto.
     * @param states Optional render states.
     *
     * Overrides Entity draw method.
     *
     * \note Passing states is optional.
     * */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    sf::RectangleShape border; ///< The border.
    const sf::Rect<float>& viewport; ///< The viewport which position viewport binds to.

    void setBorder();
};


