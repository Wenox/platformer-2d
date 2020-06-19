#pragma once

#include "View.h"
#include "Config.h"
#include "OptionsConfig.h"


class OptionsView : public View<> {
public:
    explicit OptionsView(Window& window);

    bool isSoundChecked() const;
    bool isFpsChecked() const;
    float getVolume() const;

private:
    Gui::Config<> config;
    Options::Config optionsConfig;

    void init();
    void buildGUI() override;
    void loadWidget(tgui::Widget::Ptr& widget);

    void createPanels();
    void createButtons();
    void createLabels();
    void createCheckBoxes();
    void createSoundVolumeSlider();

    void createMainPanel();
    void createButtonsPanel();

    void createFpsCheckBox();
    void createSoundCheckBox();

    void createFpsLabel();
    void createSoundLabel();
};


