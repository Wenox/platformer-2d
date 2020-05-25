#pragma once

#include <type_traits>

template <typename E>
constexpr auto to_underlying(E e) noexcept {
    return static_cast<std::underlying_type_t<E>>(e);
}

#include <optional>

template <typename E>
constexpr std::optional<int> toInt(E e) noexcept {
    if constexpr (std::is_enum<E>::value)
        return static_cast<int>(e);
    return std::nullopt;
}

template<typename T>
struct mapListOfHelper
{
    T& data;
    explicit mapListOfHelper(T& d) : data(d) {}
    mapListOfHelper& operator()(typename T::key_type    const& key,
                                typename T::mapped_type const& value) {
        data[key] = value;
        return *this;
    }
};

template<typename T>
mapListOfHelper<T> mapListOf(T& item) {
    return mapListOfHelper<T>(item);
}