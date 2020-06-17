#pragma once

#include "Consts.h"


class Settings {
public:
    bool isSoundEnabled = true;
    bool isFpsEnabled = true;
    float volume = consts::initSoundVolume;
};

extern Settings mySettings;


