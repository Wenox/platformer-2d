#pragma once

/** @file */
#include "Configuration.h"

/** \class AudioCfg
 *
 *  \ingroup Core
 *
 *  \brief Responsible for storing audio config enable.
 *
 *
 *  \note #volume default init value is customizable from config namespace.
 *
 * */
class AudioCfg {
public:
    bool isSoundEnabled = true;
    bool isFpsEnabled = true;
    float volume = config::defaultSoundVolume;
};

extern AudioCfg audioConfig;


