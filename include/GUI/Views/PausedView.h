/** @file */

#pragma once

#include "View.h"
#include "Config.h"
#include "PausedConfig.h"


/** \class PausedView
 *  \ingroup guiCore
 *  \brief View class used to draw gui within StatePaused.
 * */
class PausedView : public View<> {
public:
    /** \brief Constucts the PausedView.
     * @param Window that is bound to View base. */
    explicit PausedView(Window& window);

private:
    Gui::Config<> config;  ///< Configuration settings common to all View classes.
    Paused::Config  menuConfig; ///< Configuration settings specific to PausedView.

    /** \brief Initializes the PausedView. Effectively: calls buildGUI(). */
    void init();
    /** Creates all necessary GUI widgets, sets them correct settings, and add them to #gui. */
    void buildGUI() override;
    /** \brief Loads a given widget (likely: a button) onto the correct settings and position.
     *  @widget to be loaded.
     * \note Can be used in a loop. */
    void loadWidget(tgui::Widget::Ptr& widget);

    /** \brief Creates the main panel and adds it to the #gui. */
    void createMainPanel();
    /** \brief Create the Paused Text Image widget. */
    void createPausedTextImage();
    /** \brief Creates all buttons and adds them to the #gui. */
    void createButtons();
};


