/** @file */

#pragma once

#include "Utility.h"
#include "IConfig.h"



/** \namespace Keybinds
 *  \ingroup guiCore
 *  \brief Namespace designated for Keybinds view.
 * */
namespace Keybinds {

/** \enum Btn
 *  \ingroup guiCore
 *  \brief Keybinds buttons IDs
 *
 *  \note C++ standard libraries do not have a simple solution to convert an enum to string
 * */
    enum class Btn {
        Jump,
        RunLeft,
        RunRight,
        GoBack,
        SIZE
    };


/** \var Buttons
 *  \ingroup guiCore
 *  \brief An additional initializer list to help mapping Btn names to Strings.
 * */
    constexpr std::initializer_list<Keybinds::Btn> Buttons = {
        Btn::Jump,
        Btn::RunLeft,
        Btn::RunRight,
        Btn::GoBack
    };

    /** Make sure Initializer list size is equal to Enum */
    static_assert(Buttons.size() == toInt(Btn::SIZE));

     /** \struct Config
 *  \ingroup guiCore
 *  \brief Deriving from IConfig<Btn>, holds meaningful view configurations specific to KeybindsView.
 * */
    struct Config : public IConfig<Btn> {

        constexpr static auto offsetY = 288; ///< Starting buttons drawing offset

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


