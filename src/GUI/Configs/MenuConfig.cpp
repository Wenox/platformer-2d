#include "MenuConfig.h"

using Menu::Config;


Config::Config() {
    this->init();
}

void Config::init() {
    this->encode();
}

void Config::encode() {
    mapListOf(widgetsNames)
             (Menu::Btn::newGame,  "New Game")
             (Menu::Btn::loadGame, "Load Game")
             (Menu::Btn::options,  "Options")
             (Menu::Btn::about,    "About")
             (Menu::Btn::exit, "Exit");
}