/** @file */

#pragma once

#include "Utility.h"
#include "IConfig.h"


/** \namespace Restart
 *  \ingroup guiCore
 *  \brief Namespace designated for Restart view.
 * */
namespace Restart {
    /** \enum Btn
 *  \ingroup guiCore
 *  \brief Restart buttons IDs
 *
 *  \note C++ standard libraries do not have a simple solution to convert an enum to string
 * */
    enum class Btn {
        PlayAgain,
        Menu,
        SIZE
    };
/** \var Buttons
 *  \ingroup guiCore
 *  \brief An additional initializer list to help mapping Btn names to Strings.
 * */
    constexpr std::initializer_list<Restart::Btn> Buttons = {
        Btn::PlayAgain,
        Btn::Menu
    };

    /** Make sure Initializer list size is equal to Enum */
    static_assert(Buttons.size() == toInt(Btn::SIZE));

    /** \struct Config
 *  \ingroup guiCore
 *  \brief Deriving from IConfig<Btn>, holds meaningful view configurations specific to RestartView.
 * */
    struct Config : public IConfig<Btn> {

        constexpr static auto offsetY = 512;///< Starting buttons drawing offset Y
        constexpr static auto offsetX = 60;///< Starting buttons drawing offset X
        constexpr static auto spacing = 20;///< Space between buttons
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

