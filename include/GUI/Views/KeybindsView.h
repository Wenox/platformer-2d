/** @file */

#pragma once

#include "View.h"
#include "Config.h"
#include "KeybindsConfig.h"


/** \class KeybindsView
 *  \ingroup guiCore
 *  \brief View class used to draw gui within StateKeybinds.
 * */
class KeybindsView : public View<> {
public:
    /** \brief Constucts the KeybindsView.
     * @param Window that is bound to View base. */
    explicit KeybindsView(Window &window);

private:
    Gui::Config<> config; ///< Configuration settings common to all View classes.
    Keybinds::Config optionsConfig; ///< Configuration settings specific to KeybindsView.

    /** \brief Initializes the KeybindsView. Effectively: calls buildGUI(). */
    void init();

    /** Creates all necessary GUI widgets, sets them correct settings, and add them to #gui. */
    void buildGUI() override;
    /** \brief Loads a given widget (likely: a button) onto the correct settings and position.
     * @param widget to be loaded.
     * \note Can be used in a loop.*/
    void loadWidget(tgui::Widget::Ptr &widget);


    /** \brief Creates all panels and adds them to the #gui. */
    void createPanels();
    /** \brief Creates all buttons and adds them to the #gui. */
    void createButtons();
    /** \brief Creates all borders and adds them to the #gui. */
    void createBorders();
    /** Creates the StateKeybinds title label and adds it to the #gui. */
    void createTitleLabel();
    /** Create icons and adds them to the #gui. */
    void createIcons();

    /** \brief Creates the title panel and adds it to the #gui. */
    void createTitlePanel();

    /** Creates whole Rebinding panel group and adds it to the #gui. */
    void createRebindingPanelGroup();
    /** Creates buttons panel and adds it to the #gui. */
    void createButtonsPanel();

    /** \brief Create Rebinding Panel parent widgets holder. */
    tgui::Panel::Ptr createRebindingPanel();
    /** Adds a registering background into the parent widget.
     * @param parent of created background. */
    static void addBackgroundInto(const tgui::Panel::Ptr& parent);
    /** Adds a press key to rebind label prompt message into the parent widget.
    * @param parent of created label. */
    static void addPressKeyLabelInto(const tgui::Panel::Ptr& parent);
    /** Adds a cancel registering new keybind label prompt message into the parent.
    * @param parent of created label. */
    static void addCancelLabelInto(const tgui::Panel::Ptr& parent);

    /** Create large background icon and add it to the #gui.
     *
     * \note The icon is displayed in the middle of screen, with a show/hide animation.
     *
     * \note Icon hides when the sliding RebindingPanel appears. */
    void createLargeBgIcon();
    /** \brief Create Jump action icon and add it to the #gui. */
    void createJumpIcon();
    /** \brief Create RunLeft action icon and add it to the #gui. */
    void createRunLeftIcon();
    /** \brief Create RunRight action icon and add it to the #gui. */
    void createRunRightIcon();

    /** \brief Create left side texture border. */
    void createLeftBorder();
    /** \brief Create right side texture border. */
    void createRightBorder();
};