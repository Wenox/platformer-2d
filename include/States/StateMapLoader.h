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


template<class... Ts> struct overload : Ts... { using Ts::operator()...; };
template<class... Ts> overload(Ts...) -> overload<Ts...>;


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

            if (this->editBoxContent == "hello.bmp") {
                try {
                    mapReader = std::make_optional<BmpReader>(editBoxContent);
                    const auto &ref = std::get<BmpReader>(mapReader.value());
                    std::cout << "Is Opened: " << ref.isOpened() << std::endl;
                    ref.debugPrint();
                } catch (const std::exception &e) {
                    std::cout << "e.what(): " << e.what() << std::endl;
                }
            }
            if (this->editBoxContent == "data.txt") {
                try {
                    mapReader = std::make_optional<TxtReader>(editBoxContent);
                    const auto &ref = std::get<TxtReader>(mapReader.value());
                    std::cout << "Is Opened: " << ref.isOpened() << std::endl;
                    ref.debugPrint();
                } catch (const std::exception &e) {
                    std::cout << "e.what(): " << e.what() << std::endl;
                }
            }
        });

        gui.widgets[to_underlying(Loader::Btn::loadConfirm)]->connect("Pressed", [&]() {
                std::visit(overload{
                        [&](BmpReader &) {
                            encoder = std::make_optional<Encoder<PixelColor>>();
                            auto& data = std::get<BmpReader>(mapReader.value()).getData();
                            auto& encodedObjs = std::get<Encoder<PixelColor>>(encoder.value()).encodedObjects;
                            for (blocksNum = 0; const auto& item : data) {
                                switch (encodedObjs.find(item)->second) {
                                    case Obj::Entity::Block:
                                        ++blocksNum;
                                        break;
                                }
                            }
                            std::cout << "Creaing class game with blocksNum: " << blocksNum << std::endl;
                            /** todo: pass in Config file with blocks num, encoder etc */
                            state::gameID = stateMachine.insert(std::make_shared<StateGame>(stateMachine, resources, blocksNum, encodedObjs, data));
                            stateMachine = state::gameID;

                            },
                        [&](TxtReader &) { encoder = std::make_optional<Encoder<int>>(); }
                }, mapReader.value());
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
    int blocksNum{};

    std::optional<std::variant<BmpReader, TxtReader>> mapReader;
    std::optional<std::variant<Encoder<PixelColor>, Encoder<int>>> encoder;
};
