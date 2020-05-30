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
public:
    std::map<ReaderKey, Obj::Entity> encodedObjects;

    constexpr Encoder() {
        std::cout << "Encoder consutrctor 1\n";
        static_assert(std::is_same<ReaderKey, PixelColor>()
                   or std::is_same<ReaderKey, int>());
        std::cout << "Encoder consutrctor 2\n";

        this->encodeAll();
    }

private:
    void encodeAll() {
        std::cout << "EncodeAll start\n";
        if constexpr (std::is_same<ReaderKey, PixelColor>()) {
            std::cout << "EncodeAll PixeLColor branch\n";
            encode(PixelColor{36, 28, 237}, Obj::Entity::Block);
            encode(PixelColor{0, 0, 0},       Obj::Entity::Empty);
            encode(PixelColor{255, 0, 0},     Obj::Entity::Player);
            std::cout << "Using BMP Encoder\n";
        }
        if constexpr (std::is_same<ReaderKey, int>()) {
            std::cout << "EncodeAll TxtReader branch\n";
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

    void printDebug() {
        std::cout << "Detected encoded colors:\n";
        for (auto it = encodedObjects.begin(); it != encodedObjects.end(); it++) {
            int index = std::distance(encodedObjects.begin(), it);
            std::cout << "Encoded color: " << index + 1 << ": "
                      << (uint16_t) it->first.blue << " "
                      << (uint16_t) it->first.green << " "
                      << (uint16_t) it->first.red
                      << " encoded to Object::Type: " << it->second << std::endl;
        }
    }
};


