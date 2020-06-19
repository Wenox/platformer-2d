/** @file */

#include "OptionsConfig.h"

using Options::Config;


Config::Config() {
    this->init();
}

void Config::init() {
    this->encode();
}

void Config::encode() {
    mapListOf(widgetsNames)
             (Options::Btn::Keybinds, "Keybindings")
             (Options::Btn::GoBack,   "Go Back");
}