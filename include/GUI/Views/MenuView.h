/** @file */

#pragma once

#include "View.h"
#include "Config.h"
#include "MenuConfig.h"


/** \class MenuView
 *  \ingroup guiCore
 *  \brief View class used to draw gui within StateMenu.
 * */
class MenuView : public View<> {
public:
    /** \brief Constucts the MenuView.
     * @param Window that is bound to View base. */
    explicit MenuView(Window& window);

private:
    Gui::Config<> config; ///< Configuration settings common to all View classes.
    Menu::Config  menuConfig; ///< Configuration settings specific to MenuView.

    /** \brief Initializes the MenuView. Effectively: calls buildGUI(). */
    void init();
    /** Creates all necessary GUI widgets, sets them correct settings, and add them to #gui. */
    void buildGUI() override;
    /** \brief Loads a given widget (likely: a button) onto the correct settings and position.
     * @param widget to be loaded.
     * \note Can be used in a loop.*/
    void loadWidget(tgui::Widget::Ptr& widget);

    /** \brief Creates the main panel and adds it to the #gui. */
    void createMainPanel();
    /** \brief Creates all buttons and adds them to the #gui. */
    void createButtons();
};


