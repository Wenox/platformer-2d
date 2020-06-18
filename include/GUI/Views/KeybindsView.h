#pragma once

#include "View.h"
#include "Config.h"
#include "KeybindsConfig.h"


class KeybindsView : public View<> {
public:
    explicit KeybindsView(Window &window);

private:
    Gui::Config<> config;
    Keybinds::Config optionsConfig;

    void init();
    void buildGUI() override;
    void loadWidget(tgui::Widget::Ptr &widget);


    void createPanels();
    void createButtons();
    void createBorders();
    void createTitleLabel();
    void createIcons();


    void createTitlePanel();
    void createRebindingPanelGroup();
    void createButtonsPanel();
    
    tgui::Panel::Ptr createRebindingPanel();
    static void addBackgroundInto(const tgui::Panel::Ptr& parent);
    static void addPressKeyLabelInto(const tgui::Panel::Ptr& parent);
    static void addCancelLabelInto(const tgui::Panel::Ptr& parent);

    void createLargeBgIcon();
    void createJumpIcon();
    void createRunLeftIcon();
    void createRunRightIcon();

    void createLeftBorder();
    void createRightBorder();
};