#pragma once

#include "View.h"
#include "Config.h"
#include "MapLoaderConfig.h"


class MapLoaderView : public View<> {
public:
    explicit MapLoaderView(Window& window);

    void clearMapNameBoxWithPrompt();
    void clearMapNameBox();

    void setBadMapLabelVisible(bool visibilityStatus);
    void animateBadMapLabel();

    std::string getMapName() const;

    void setPromptToEnter(bool status);
    bool isPromptToEnter() const;

private:
    Gui::Config<> config;
    Loader::Config loaderConfig;

    void init();
    void buildGUI() override;
    void loadWidget(tgui::Widget::Ptr& widget);

    bool promptToEnter{};
};


