/** @file */

/** @defgroup guiCore GUI
 *  Classes responsible for View layer inside varying Menus.
 *  @{
 */

/** @} */ // end of group1


#pragma once

#include "Configuration.h"


/** \namespace Gui
 *  \ingroup guiCore
 *  \brief Encapsulate common global View Config within an additional namespace.
 * */
namespace Gui {

    /** \struct Config
 *  \ingroup guiCore
 *  \brief A shared gui config. Contains common settings.
     *
     *  Exemplary  constexpr Config settings commonto all View classes:
     *
     *  - Buttonwidth: #width = 250
     *  - ButtonHeight: #height = 50
     *  - #testSize = 24
     *  - #opacity = 0.95
     *  - #font
     *  - #borderColor
     *  - #backgroundColor
     *
     *
 * */
    template <typename Widget = tgui::Widget::Ptr>
    struct Config {
        constexpr static auto width       = 250;
        constexpr static auto height      = 50;
        constexpr static auto textSize    = 24;
        constexpr static auto opacity     = 0.95;


        const static inline tgui::Font font = {config::widgetsFontName.data()};


        const tgui::Color borderColor     = {209, 153, 48};
        const tgui::Color backgroundColor = {255, 50, 245};


        /** \brief Prepares a given widget to be ready to be displayed.
         *
         * An extra 'if constexpr' branch is executed for Buttons that sets the #borderColor and #backgroundColor.
         *
         * */
        void prepare(Widget widget) {
            widget->setSize(tgui::Layout2d{width, height});
            widget->setInheritedOpacity(opacity);
            widget->setTextSize(textSize);
            widget->setInheritedFont(font);

            if constexpr (std::is_same<Widget, tgui::Button::Ptr>::value) {
                widget->getRenderer()->setBorderColor(borderColor);
                widget->getRenderer()->setBackgroundColor(backgroundColor);
            }
        }
    };
}