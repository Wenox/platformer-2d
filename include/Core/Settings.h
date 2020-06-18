#pragma once

#include "Consts.h"


class AudioCfg {
public:
    bool isSoundEnabled = true;
    bool isFpsEnabled = true;
    float volume = config::defaultSoundVolume;
};

extern AudioCfg audioConfig;


