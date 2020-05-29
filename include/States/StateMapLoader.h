#pragma once

#include <GUI/MapLoaderGUI.h>
#include <Encoder/BmpReader.h>
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

            /** todo: to be cleaned up */

            if (this->editBoxContent == "hello.bmp") {
                try {
                    bmpReader = std::make_optional<BmpReader>(editBoxContent);
                    std::cout << "Is Opened: " << bmpReader->isOpened() << std::endl;
                    bmpReader->debugPrint();
                } catch(const std::exception& e) {
                    std::cout << "e.what(): " << e.what() << std::endl;
                }
            }
        });
    }

    void onDestroy() override {

    }

    void processInput() override {

    }

    void update(float) override {
        gui.handleEvent(window.getEvent());

    }

    void draw(Window&) override {
        gui.draw();
    }

private:
    StateMachine& stateMachine;
    Window& window;
    MapLoaderGUI gui;

    std::string editBoxContent{};

    std::optional<BmpReader> bmpReader;
};















