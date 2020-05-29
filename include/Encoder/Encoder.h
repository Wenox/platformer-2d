#pragma once

#include <map>
#include <iostream>
#include "PixelColor.h"

#if (__cplusplus == 202002L)
template <typename Key>
    concept Mappable = std::strict_weak_order<std::less<Key>, Key, Key>;
#endif

namespace Obj {
    enum class Entity {
        Empty,
        Block,
        Player
    };
}

template <typename ReaderKey>
#if (__cplusplus == 202002L)
    requires Mappable<Key>
#endif
class Encoder {
    std::map<ReaderKey, Obj::Entity> encodedObjects;

public:
    constexpr Encoder() {
        static_assert(std::is_same<ReaderKey, PixelColor>()
                   or std::is_same<ReaderKey, int>());

        this->encodeAll();
    }

private:
    void encodeAll() {
        if constexpr (std::is_same<ReaderKey, PixelColor>()) {
            encode(PixelColor{255, 255, 255}, Obj::Entity::Block);
            encode(PixelColor{0, 0, 0},       Obj::Entity::Empty);
            encode(PixelColor{255, 0, 0},     Obj::Entity::Player);
            std::cout << "Using BMP Encoder\n";
        }
        if constexpr (std::is_same<ReaderKey, int>()) {
            encode(0, Obj::Entity::Block);
            encode(1, Obj::Entity::Empty);
            encode(2, Obj::Entity::Player);
            std::cout << "Using TXT Encoder\n";
        }
    }

    void encode(const ReaderKey& key, Obj::Entity entity) {
        static_assert(std::is_same<typename std::decay<decltype(key)>::type , ReaderKey>());
        encodedObjects.insert(std::make_pair(key, entity));
    }
};


