/** @file */

#pragma once

#include "View.h"
#include "Config.h"
#include "RestartConfig.h"
#include "ResourceManager.h"

/** \class RestartView
 *  \ingroup guiCore
 *  \brief View class used to draw gui within StateRestart.
 * */
class RestartView : public View<> {
public:
    /** \brief Constucts the RestartView.
     * @param Window that is bound to View base.
     * @param resourceManager containing required textures references. */
    explicit RestartView(Window& window, ResourceManager& resourceManager);

    /** Set the #gameFinishedImage to a #wonTexture. */
    void setGameWonTexture();
    /** Set #gameFinishedImage to a #lostTexture. */
    void setGameLostTexture();

private:
    Gui::Config<> config;  ///< Configuration settings common to all View classes.
    Restart::Config  restartConfig; ///< Configuration settings specific to RestartView.

    const sf::Texture& lostTexture;
    const sf::Texture& wonTexture;

    tgui::Picture::Ptr gameFinishedImage;

    /** \brief Initializes the RestartView. Effectively: calls buildGUI(). */
    void init();
    /** \brief Creates all necessary GUI widgets, sets them correct settings, and add them to #gui. */
    void buildGUI() override;

    /** \brief Loads a given widget (likely: a button) onto the correct settings and position.
     * @widget to be loaded.
     * \note Can be used in a loop. */
    void loadWidget(tgui::Widget::Ptr& widget);

    /** \brief Creates all panels and adds them to the #gui. */
    void createPanels();
    /** \brief Creates all buttons and adds them to the #gui. */
    void createButtons();
    /** \brief Creates the gameFinishedImage which is either a #lostTexture or #wonTexture.
     *
     * \note There is no dynamic memory allocation. The pointers bind to references that already existed. */
    void createGameFinishedImage();
    /** \brief Creates the main panel and adds it to the #gui. */
    void createMainPanel();
    /** \brief Creates the buttons panel and adds it to the #gui. */
    void createButtonsPanel();
};