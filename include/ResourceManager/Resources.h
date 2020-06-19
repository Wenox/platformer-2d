/** @file */
#pragma once

/** \namespace res
 *
 * \ingroup myresourcez
 *
 * \brief Namespace wrapper over Resources enum IDs.
 *
 * */
namespace res {

    /** \enum Texture
     *
     * \ingroup myresourcez
     *
     * \brief Available Texture IDs.
     * */
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

    /** \enum Sound
     *
     * \ingroup myresourcez
     *
     * \brief Available Sound IDs.
     * */
    enum class Sound {
        Collect,
        BtnHover,
        Death,
        WinGame
    };

    /** \enum Music
     *
     * \ingroup myresourcez
     *
     * \brief Available Music IDs.
     * */
    enum class Music {
        Background
    };
}