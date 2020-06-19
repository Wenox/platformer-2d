/** @file */

#pragma once

#include <map>
#include <iostream>
#include "PixelColor.h"

#if (__cplusplus == 202002L)

/** \brief Define a Mappable concept (C++20) for better error messages. */
template <typename Key>
    concept Mappable = std::strict_weak_order<std::less<Key>, Key, Key>; ///< \note \warnng Define a Mappable concept (C++20) for better error messages.
#endif

/** \namespace Obj
*
*  \ingroup Encoder
*
*  \brief Available game entity objects. Used only in StateGame.
*
*
*  */
namespace Obj {

    enum class Entity {
        Empty,
        Player,
        Objective,
        HeartCollectible,

        BlockRed,
        BlockBlue,
        BlockBrown,
        BlockGray,
        BlockGreen,
        BlockPurple,
        BlockYellow,
        BlockCrate,
        Water1,
        Water2,
        Sign1,
        Sign2,

        Spike,
        SpikeLeft,
        SpikeRight,
        SpikeTop
    };
}



/** \class Encoder
 *
 * \ingroup Encoder
 *
 * \brief Encodes PixelColor (bmp) or int (txt) into Obj::Entity entities, depending on the variant type.
 *
 * Uses custom Mappable concept (C++20) for validating if a ReaderKey is mappable type.
 * In case of C++17 compiler, the Mappable concept is omitted.
 *
 *
 * */
template <typename ReaderKey>
#if (__cplusplus == 202002L)
    requires Mappable<Key>
#endif
class Encoder {
public:
    std::map<ReaderKey, Obj::Entity> encodedObjects;

    /** \brief Validates ReaderKey type and creates an Encoder of that type.
     *
     * Available ReaderKey types:
     *   - PixelColor (when map is Bmp)
     *   - int (when map is Txt)
     * */
    constexpr Encoder() {
        static_assert(std::is_same<ReaderKey, PixelColor>()
                   or std::is_same<ReaderKey, int>());

        this->encodeAll();
    }

private:

    /** \brief Encodes all PixelColor or int into Obj::Entity entities.
     *
     * \note One of two branches is executed based on constexpr evaluation.
     *
     * */
    void encodeAll() {
        if constexpr (std::is_same<ReaderKey, PixelColor>()) {
            encode(PixelColor{0, 0, 0},       Obj::Entity::Empty);
            encode(PixelColor{201, 174, 255}, Obj::Entity::Player);             ///< Light pink
            encode(PixelColor{255, 255, 255}, Obj::Entity::Objective);          ///< White
            encode(PixelColor{231, 191, 200}, Obj::Entity::HeartCollectible);   ///< Light violet

            encode(PixelColor{36, 28, 237},   Obj::Entity::BlockRed);
            encode(PixelColor{232, 162, 0},   Obj::Entity::BlockBlue);
            encode(PixelColor{21, 0, 136},    Obj::Entity::BlockBrown);         ///< Dark brown
            encode(PixelColor{127, 127, 127}, Obj::Entity::BlockGray);
            encode(PixelColor{76, 177, 34},   Obj::Entity::BlockGreen);
            encode(PixelColor{164, 73, 163},  Obj::Entity::BlockPurple);
            encode(PixelColor{0, 242, 255},   Obj::Entity::BlockYellow);
            encode(PixelColor{87, 122, 185},   Obj::Entity::BlockCrate);

            encode(PixelColor{204, 72, 63},   Obj::Entity::Water1);             ///< Dark blue
            encode(PixelColor{190, 146, 112},   Obj::Entity::Water2);           ///< Soft dark blue
            encode(PixelColor{39, 127, 255},   Obj::Entity::Sign1);             ///< Orange
            encode(PixelColor{14, 201, 255},   Obj::Entity::Sign2);             ///< Soft orange

            encode(PixelColor{195, 195, 195}, Obj::Entity::Spike);              ///< Light grey
            encode(PixelColor{194, 195, 195}, Obj::Entity::SpikeLeft);          ///< Light grey
            encode(PixelColor{195, 194, 195}, Obj::Entity::SpikeRight);         ///< Light grey
            encode(PixelColor{195, 195, 194}, Obj::Entity::SpikeTop);           ///< Light grey
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
            encode(11, Obj::Entity::BlockCrate);

            encode(12,  Obj::Entity::Water1);
            encode(13,   Obj::Entity::Water2);
            encode(14,   Obj::Entity::Sign1);
            encode(15,   Obj::Entity::Sign2);

            encode(10, Obj::Entity::Spike);
        }
    }

    /** \brief Encodes a single Readerkey onto Obj::Entity entity
     *
     * \param key Map key of type ReaderKey which is a Mappable either PixelColor or int.
     * \param entity Value for the key to be mapped to.
     *
     *
     * */
    void encode(const ReaderKey& key, Obj::Entity entity) {
        static_assert(std::is_same<typename std::decay<decltype(key)>::type , ReaderKey>());
        encodedObjects.insert(std::make_pair(key, entity));
    }

    /** \bref Prints formatted encoder debug info.
     *
     * \note Supports only non-trivial Bmp type.
     *
     * */
    void printDebug() { /** todo: add support for txt */
        std::cout << "Detected encoded colors:\n";
        for (auto it = encodedObjects.begin(); it != encodedObjects.end(); it++) {
            int index = std::distance(encodedObjects.begin(), it);
            std::cout << "Encoded color: " << index + 1 << ": "
                      << static_cast<uint16_t>(it->first.blue)  << " "
                      << static_cast<uint16_t>(it->first.green) << " "
                      << static_cast<uint16_t>(it->first.red)    << " "
                      << " encoded to Object::Type: " << it->second << std::endl;
        }
    }
};


