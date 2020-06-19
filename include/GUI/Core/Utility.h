/** @file */

#pragma once

#include <type_traits>
#include <optional>


/** \brief Converts an argument (Enum) to its underlying type.
 * \ingroup guiCore
 *  @param An enum
 *  @returns An underlying type
 *
 *  Templates meta-programming.
 *
 *  Used to access View widgets.
 *
 *  */
template <typename E>
constexpr auto to_underlying(E e) noexcept {
    return static_cast<std::underlying_type_t<E>>(e);
}


/** \brief Converts an argument (Enum) to integer.
 * \ingroup guiCore
 * @param an enum
 * @returns an integer value of enum item
 *
 * \note uses if constexpr
 * */
template <typename E>
constexpr std::optional<int> toInt(E e) noexcept {
    if constexpr (std::is_enum<E>::value)
        return static_cast<int>(e);
    return std::nullopt;
}

/** \brief A helper for mapListOf converter.
 * \ingroup guiCore*/
template<typename T>
struct mapListOfHelper
{
    T& data;
    constexpr explicit mapListOfHelper(T& d) : data(d) {}
    constexpr mapListOfHelper& operator()(typename T::key_type    const& key,
                                          typename T::mapped_type const& value) {
        data[key] = value;
        return *this;
    }
};

/** mapListOf converter, alternatively use Boost implementation.
 * \ingroup guiCore
 * \note Using Boost implementation adds extra library complexity. */
template<typename T>
constexpr  mapListOfHelper<T> mapListOf(T& item) {
    return mapListOfHelper<T>(item);
}