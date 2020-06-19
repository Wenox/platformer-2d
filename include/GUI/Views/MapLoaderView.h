/** @file */

#pragma once

#include "View.h"
#include "Config.h"
#include "MapLoaderConfig.h"


/** \class MapLoaderView
 *  \ingroup guiCore
 *  \brief View class used to draw gui within StateMapLoader.
 * */
class MapLoaderView : public View<> {
public:
    /** \brief Constucts the MapLoaderView.
     * @param Window that is bound to View base. */
    explicit MapLoaderView(Window& window);

    /** Clears the map name edit box with >Enter map name...< message */
    void clearMapNameBoxWithPrompt();
    /** Clears the map name edit box. */
    void clearMapNameBox();

    /** Sets the badMapLabel visibility to a given status.
     * @param visibilityStatus */
    void setBadMapLabelVisible(bool visibilityStatus);
    /** Slide animation on show and hide of >No such file!< label. */
    void animateBadMapLabel();

    /** Retrieve the map name.
     * @returns the map name*/
    std::string getMapName() const;

    /** Sets #promptToEnterMapName to a given status.
     * @param status new status. */
    void setPromptToEnter(bool status);
    /** Check if player is currently #promptToEnterMapName.
     *  @returns Is bad map label prompt visible?*/
    bool isPromptToEnter() const;

private:
    Gui::Config<> config; ///< Configuration settings common to all View classes.
    Loader::Config loaderConfig; ///< Configuration settings specific to MapLoaderView.

    bool promptToEnterMapName{}; ///< Is currently prompt to re-enter map name?

    /** \brief Initializes the MapLoaderView. Effectively: calls buildGUI(). */
    void init();
    /** Creates all necessary GUI widgets, sets them correct settings, and add them to #gui. */
    void buildGUI() override;
    /** \brief Loads a given widget (likely: a button) onto the correct settings and position.
     * @param widget to be loaded.
     * \note Can be used in a loop. */
    void loadWidget(tgui::Widget::Ptr& widget);

    /** \brief Creates the main panel and adds it to the #gui. */
    void createMainPanel();
    /** \brief Creates all buttons and adds them to the #gui. */
    void createButtons();
    /** Create an edit box where user types in his map name to the #gui. */
    void createMapNameBox();
    /** Create a label showing >No such file!< when user enters bad map name, and add it to the #gui. */
    void createBadMapLabel();
};


