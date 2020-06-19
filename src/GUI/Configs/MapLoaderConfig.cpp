/** @file */

#include <iostream>
#include "MapLoaderConfig.h"

using Loader::Config;


Config::Config() {
    this->init();
}


void Config::init() {
    this->encode();
}

void Config::encode() {
    mapListOf(widgetsNames)
             (Loader::Btn::loadMap,     "Load map")
             (Loader::Btn::openEditor,  "Build new map")
             (Loader::Btn::goBack,      "Go back");
}