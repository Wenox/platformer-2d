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
        Player,
        Objective,

        BlockRed,
        BlockBlue,
        BlockBrown,
        BlockGray,
        BlockGreen,
        BlockPurple,
        BlockYellow,

        Spike,
        SpikeLeft,
        SpikeRight,
        SpikeTop
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
        static_assert(std::is_same<ReaderKey, PixelColor>()
                   or std::is_same<ReaderKey, int>());

        this->encodeAll();
    }

private:
    void encodeAll() {
        if constexpr (std::is_same<ReaderKey, PixelColor>()) {
            encode(PixelColor{0, 0, 0},       Obj::Entity::Empty);
            encode(PixelColor{201, 174, 255}, Obj::Entity::Player);      ///< Light pink
            encode(PixelColor{255, 255, 255}, Obj::Entity::Objective);   ///< White

            encode(PixelColor{36, 28, 237},   Obj::Entity::BlockRed);
            encode(PixelColor{232, 162, 0},   Obj::Entity::BlockBlue);
            encode(PixelColor{21, 0, 136},    Obj::Entity::BlockBrown);  ///< Dark brown
            encode(PixelColor{127, 127, 127}, Obj::Entity::BlockGray);
            encode(PixelColor{76, 177, 34},   Obj::Entity::BlockGreen);
            encode(PixelColor{164, 73, 163},  Obj::Entity::BlockPurple);
            encode(PixelColor{0, 242, 255},   Obj::Entity::BlockYellow);

            encode(PixelColor{195, 195, 195}, Obj::Entity::Spike);        ////< Light grey
            encode(PixelColor{194, 195, 195}, Obj::Entity::SpikeLeft);        ////< Light grey
            encode(PixelColor{195, 194, 195}, Obj::Entity::SpikeRight);        ////< Light grey
            encode(PixelColor{195, 195, 194}, Obj::Entity::SpikeTop);        ////< Light grey
        }
        if constexpr (std::is_same<ReaderKey, int>()) {
            encode(0, Obj::Entity::Empty);
            encode(1, Obj::Entity::Player);
            encode(9, Obj::Entity::Objective);

            encode(2, Obj::Entity::BlockRed);
            encode(3, Obj::Entity::BlockBlue);
            encode(4, Obj::Entity::BlockBrown);
            encode(5, Obj::Entity::BlockGray);
            encode(6, Obj::Entity::BlockGreen);
            encode(7, Obj::Entity::BlockPurple);
            encode(8, Obj::Entity::BlockYellow);

            encode(10, Obj::Entity::Spike);
        }
    }

    void encode(const ReaderKey& key, Obj::Entity entity) {
        static_assert(std::is_same<typename std::decay<decltype(key)>::type , ReaderKey>());
        encodedObjects.insert(std::make_pair(key, entity));
    }

    void printDebug() { /** todo: add support for txt */
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


