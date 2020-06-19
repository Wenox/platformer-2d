/** @file */

#pragma once

#include <map>



/** \struct IConfig
 *  \ingroup guiCore
 *  \brief Every specific Config inherits from this struct
 *
 *  \note Deriving classes must implement encode pure virtual method.
 *
 *  \warning The <em>E</em> template type has to be an <em>Enum</em>.
 * */
template <typename E>
struct IConfig {
    static_assert(std::is_enum<E>::value, "IConfig: E mustn't be Enum");

    std::map<E, const char*> widgetsNames;

/** C++20: constexpr virtual */
#if (__cplusplus == 202002L)
    constexpr
#endif
    virtual void encode() = 0;
};