#pragma once

#include "Consts.h"


class AudioCfg {
public:
    bool isSoundEnabled = true;
    bool isFpsEnabled = true;
    float volume = consts::initSoundVolume;
};

extern AudioCfg audioConfig;


