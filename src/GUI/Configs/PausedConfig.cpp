#include "PausedConfig.h"

using Paused::Config;


Config::Config() {
    this->init();
}

void Config::init() {
    this->encode();
}

void Config::encode() {
    mapListOf(widgetsNames)
             (Paused::Btn::resume,  "Resume")
             (Paused::Btn::options, "Options")
             (Paused::Btn::menu,    "Main menu");
}