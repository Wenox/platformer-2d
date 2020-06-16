#pragma once

namespace res {
    enum class Texture {
        BlockRed,
        BlockBlue,
        BlockBrown,
        BlockGray,
        BlockGreen,
        BlockPurple,
        BlockYellow,

        Player,
        PlayerLeft,
        PlayerRight,

        Objective,

        Heart,
        HeartEmpty,

        BgClouds,
        BgPaused,
        BgOptions,

        Spike,

        OptionsLeftTopCorner,
        OptionsLeftBotCorner,
        OptionsRightBotCorner,
        OptionsRightTopCorner,

        GameOver,
        GameWon
    };

    enum class Sound {
        Bullet,
        Bing,
        Death
    };

    enum class Music {
        Ambient
    };
}