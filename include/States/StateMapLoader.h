#pragma once

#include <GUI/MapLoaderGUI.h>
#include "State.h"
#include "StateMachine.h"


class StateMapLoader : public State {
public:

    StateMapLoader(StateMachine& stateMachine, Window& window)
        : stateMachine{stateMachine}
        , window{window}
        , gui{window}
    {
        std::cout << "StateMapLoader::StateMapLoader()\n";
    }

    void onCreate() override {
        gui.widgets[to_underlying(Loader::Btn::newMap)]->connect("Pressed", [&]() {
            stateMachine = state::gameID;
        });
        gui.widgets[to_underlying(Loader::Btn::loadMap)]->connect("Pressed", [&]() {
            stateMachine = state::menuID;
        });
        gui.widgets[to_underlying(Loader::Btn::loadConfirm)]->connect("Pressed", [&]() {
            this->editBoxContent = gui.getGui().getContainer()->get<tgui::EditBox>("editBox")->getText().toAnsiString();
            gui.getGui().getContainer()->get<tgui::EditBox>("editBox")->setText("");
            gui.getGui().getContainer()->get<tgui::Label>("editBoxLabel")->setTextSize(gui.config.textSize - 5);
            gui.getGui().getContainer()->get<tgui::Label>("editBoxLabel")->getRenderer()->setTextColor(tgui::Color{255, 0, 0});
            gui.getGui().getContainer()->get<tgui::Label>("editBoxLabel")->setText("No such file");
            gui.getGui().getContainer()->get<tgui::Label>("editBoxLabel")->showWithEffect(tgui::ShowAnimationType::SlideFromLeft, sf::milliseconds(300));
        });
    }

    void onDestroy() override {

    }

    void processInput() override {

    }

    void update(float) override {
        gui.handleEvent(window.getEvent());
        if (this->editBoxContent == "jd.bmp") {
            const auto& dis = gui.getGui().getContainer()->get<tgui::Label>("editBoxLabel");
            dis->setVisible(true);
            dis->getRenderer()->setTextColor(tgui::Color{255, 255, 0});
            dis->setText("OK! :)");
            dis->setTextSize(32);
            dis->showWithEffect(tgui::ShowAnimationType::Fade, sf::milliseconds(1600));
        }
    }

    void draw(Window&) override {
        gui.draw();
    }

private:
    StateMachine& stateMachine;
    Window& window;
    MapLoaderGUI gui;

    std::string editBoxContent{};
};


