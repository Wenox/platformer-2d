#pragma once

#include <map>


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