/** @file */

#include "MenuConfig.h"
#include "RestartConfig.h"

using Restart::Config;


Config::Config() {
    this->init();
}

void Config::init() {
    this->encode();
}

void Config::encode() {
    mapListOf(widgetsNames)
             (Restart::Btn::PlayAgain,  "Play Again")
             (Restart::Btn::Menu,       "Main Menu");
}