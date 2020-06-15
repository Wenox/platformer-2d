#pragma once

#include <Window.h>
#include "MapLoaderConfig.h"
#include "GUI.h"
#include "Config.h"


class MapLoaderGUI : public GUI<> {
public:
    explicit MapLoaderGUI(Window& window);

    Gui::Config<> config;

private:
    Loader::Config loaderConfig;
    int btnIndex{};

    void init();
    void buildGUI() override;
    void loadWidget(tgui::Widget::Ptr& widget);

    bool promptToEnter{};
public:
    void setPromptToEnter(bool status) { promptToEnter = status; }
    bool isPromptToEnter() const { return promptToEnter; }

    auto getMapName() {
        return this->getGui().getContainer()->get<tgui::EditBox>("mapNameBox")->getText().toAnsiString();
    }

    void clearMapNameBoxWithPrompt() {
        this->promptToEnter = true;
        const auto& mapNameBox = this->getGui().getContainer()->get<tgui::EditBox>("mapNameBox");
        mapNameBox->setText({"Enter map name..."});
    }

    void clearMapNameBox() {
        this->getGui().getContainer()->get<tgui::EditBox>("mapNameBox")->setText({});
    }



    void setBadMapLabelVisible(bool visibilityStatus) {
        this->getGui().getContainer()->get<tgui::Label>("badMapLabel")->setVisible(visibilityStatus);
    }

    void animateBadMapLabel() {
        const auto& badMapLabel = this->getGui().getContainer()->get<tgui::Label>("badMapLabel");
        badMapLabel->showWithEffect(tgui::ShowAnimationType::SlideFromLeft, sf::milliseconds(300));
    }
};


