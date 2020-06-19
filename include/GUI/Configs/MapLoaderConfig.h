/** @file */

#pragma once

#include <TGUI/Color.hpp>
#include "Utility.h"
#include "IConfig.h"

/** \namespace Loader
 *  \ingroup guiCore
 *  \brief Namespace designated for MapLoader view.
 * */
namespace Loader {
    /** \enum Btn
 *  \ingroup guiCore
 *  \brief MapLoader buttons IDs
 *
 *  \note C++ standard libraries do not have a simple solution to convert an enum to string
 * */
    enum class Btn {
        loadMap,
        openEditor,
        goBack,
        SIZE
    };

    /** \var Buttons
 *  \ingroup guiCore
 *  \brief An additional initializer list to help mapping Btn names to Strings.
 * */
    constexpr std::initializer_list<Loader::Btn> Buttons = {
        Btn::loadMap,
        Btn::openEditor,
        Btn::goBack
    };

    /** Make sure Initializer list size is equal to Enum */
    static_assert(Buttons.size() == toInt(Btn::SIZE));

    /** \struct Config
 *  \ingroup guiCore
 *  \brief Deriving from IConfig<Btn>, holds meaningful view configurations specific to MapLoaderView.
 * */
    struct Config : public IConfig<Btn> {
        tgui::Color mapNameColor = {196, 0, 0}; ///< The color of map name text font.

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


