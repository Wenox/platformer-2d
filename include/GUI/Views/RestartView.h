#pragma once

#include "View.h"
#include "Config.h"
#include "RestartConfig.h"
#include "ResourceManager.h"


class RestartView : public View<> {
public:
    explicit RestartView(Window& window, ResourceManager& resourceManager);

    void setGameWonTexture();
    void setGameLostTexture();

private:
    Gui::Config<> config;
    Restart::Config  restartConfig;

    const sf::Texture& lostTexture;
    const sf::Texture& wonTexture;

    tgui::Picture::Ptr gameFinishedImage;

    void init();
    void buildGUI() override;
    void loadWidget(tgui::Widget::Ptr& widget);

    void createPanels();
    void createButtons();
    void createGameFinishedImage();

    void createMainPanel();
    void createButtonsPanel();
};