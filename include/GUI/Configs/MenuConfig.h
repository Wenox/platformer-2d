/** @file */

#pragma once

#include "Utility.h"
#include "IConfig.h"


/** \namespace Menu
 *  \ingroup guiCore
 *  \brief Namespace designated for Menu view.
 * */
namespace Menu {
    /** \enum Btn
 *  \ingroup guiCore
 *  \brief Menu buttons IDs
 *
 *  \note C++ standard libraries do not have a simple solution to convert an enum to string
 * */
    enum class Btn {
        newGame,
        loadGame,
        options,
        about,
        exit,
        SIZE
    };

    /** \var Buttons
 *  \ingroup guiCore
 *  \brief An additional initializer list to help mapping Btn names to Strings.
 * */
    constexpr std::initializer_list<Menu::Btn> Buttons = {
        Btn::newGame,
        Btn::loadGame,
        Btn::options,
        Btn::about,
        Btn::exit
    };

    /** Make sure Initializer list size is equal to Enum */
    static_assert(Buttons.size() == toInt(Btn::SIZE));

    /** \struct Config
 *  \ingroup guiCore
 *  \brief Deriving from IConfig<Btn>, holds meaningful view configurations specific to MenuView.
 * */
    struct Config : public IConfig<Btn> {

        constexpr static auto offsetY = 45; ///< Starting buttons drawing offset

        /** Create a Config. */
        Config();

#if (__cplusplus == 202002L)
        constexpr
#endif
        /** Run encode. */
        void init();

#if (__cplusplus == 202002L)
        constexpr
#endif
/** Encode button enum accessors to a given strings. */
        void encode() override;
    };
}

