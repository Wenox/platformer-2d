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
        BgAbout,

        Spike,

        OptionsLeftTopCorner,
        OptionsLeftBotCorner,
        OptionsRightBotCorner,
        OptionsRightTopCorner,

        GameLost,
        GameWon
    };

    enum class Sound {
        Collect,
        BtnHover,
        Death,
        WinGame
    };

    enum class Music {
        Background
    };
}