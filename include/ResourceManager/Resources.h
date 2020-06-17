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
        BlockCrate,
        Water1,
        Water2,
        Sign1,
        Sign2,

        Player,
        PlayerLeft,
        PlayerRight,

        Objective,

        Heart,
        HeartEmpty,

        BgGame,
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
        Arcade
    };
}