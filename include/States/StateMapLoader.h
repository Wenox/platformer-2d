#pragma once

#include <GUI/MapLoaderGUI.h>
#include <Encoder/BmpReader.h>
#include <Encoder/TxtReader.h>
#include <variant>
#include <Encoder/Encoder.h>
#include <Game.h>
#include "State.h"
#include "StateMachine.h"
#include "StateGame.h"
#include "MapLoader.h"

//template<class... Ts> struct overload : Ts... { using Ts::operator()...; };
//template<class... Ts> overload(Ts...) -> overload<Ts...>;


class StateMapLoader : public State {
public:

    StateMapLoader(Game& game)
        : stateMachine{game.getStateMachine()}
        , window{game.getWindow()}
        , resources{game.getResources()}
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
            gui.getGui().getContainer()->get<tgui::Label>("editBoxLabel")->getRenderer()->setTextColor(
                    tgui::Color{255, 0, 0});
            gui.getGui().getContainer()->get<tgui::Label>("editBoxLabel")->setText("No such file");
            gui.getGui().getContainer()->get<tgui::Label>("editBoxLabel")->showWithEffect(
                    tgui::ShowAnimationType::SlideFromLeft, sf::milliseconds(300));

            /** todo: to be cleaned up */
        });

        gui.widgets[to_underlying(Loader::Btn::loadConfirm)]->connect("Pressed", [&]() {
            if (this->editBoxContent == "hello.bmp") {
                mapLoader = std::make_optional<MapLoader<Bmp>>(editBoxContent);
            }
            if (this->editBoxContent == "data.txt") {
                mapLoader = std::make_optional<MapLoader<Txt>>(editBoxContent);
            }
            state::gameID = stateMachine.insert(std::make_shared<StateGame>(stateMachine, resources, mapLoader.value()));
            stateMachine = state::gameID;
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
    ResourceManager& resources;

    MapLoaderGUI gui;
    std::string editBoxContent{};


    std::optional<std::variant<MapLoader<Bmp>, MapLoader<Txt>>> mapLoader;
};
