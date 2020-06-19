/** @file */

#pragma once

#include "View.h"
#include "Config.h"
#include "OptionsConfig.h"


/** \class OptionsView
 *  \ingroup guiCore
 *  \brief View class used to draw gui within StateOptions.
 * */
class OptionsView : public View<> {
public:
    /** \brief Constucts the OptionsView.
     * @param Window that is bound to View base. */
    explicit OptionsView(Window& window);

    bool isSoundChecked() const;
    bool isFpsChecked() const;
    float getVolume() const;

private:
    Gui::Config<> config;  ///< Configuration settings common to all View classes.
    Options::Config optionsConfig; ///< Configuration settings specific to OptionsView.

    /** \brief Initializes the OptionsView. Effectively: calls buildGUI(). */
    void init();
    /** Creates all necessary GUI widgets, sets them correct settings, and add them to #gui. */
    void buildGUI() override;
    /** \brief Loads a given widget (likely: a button) onto the correct settings and position.
     *  @param widget to be loaded.
     * \note Can be used in a loop. */
    void loadWidget(tgui::Widget::Ptr& widget);

    /** \brief Creates all panels and adds them to the #gui. */
    void createPanels();
    /** \brief Creates all buttons and adds them to the #gui. */
    void createButtons();
    /** \brief Creates all labels and adds them to the #gui. */
    void createLabels();
    /** \brief Creates all check Boxes and adds them to the #gui. */
    void createCheckBoxes();
    /** \brief Creates a sound volume slider and adds it to the #gui. */
    void createSoundVolumeSlider();

    /** \brief Creates the main panel and adds it to the #gui. */
    void createMainPanel();
    /** \brief Creates the buttons panel and adds it to the #gui. */
    void createButtonsPanel();

    /** \brief Creates FPS enable check box and adds it to the #gui. */
    void createFpsCheckBox();
    /** \brief Creates sound enable check box and adds it to the #gui. */
    void createSoundCheckBox();

    /** \brief Creates FPS enabled label and adds it to the #gui. */
    void createFpsLabel();
    /** \brief Creates sound enabled label box and adds it to the #gui. */
    void createSoundLabel();
};


