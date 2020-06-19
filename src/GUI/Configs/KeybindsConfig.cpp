#include "KeybindsConfig.h"

using Keybinds::Config;


Config::Config() {
    this->init();
}


void Config::init() {
    this->encode();
}

void Config::encode() {
    mapListOf(widgetsNames)
             (Keybinds::Btn::Jump,     "Jump")
             (Keybinds::Btn::RunLeft,  "Run Left")
             (Keybinds::Btn::RunRight, "Run Right")
             (Keybinds::Btn::GoBack,   "Go Back");
}