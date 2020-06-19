/** @file */
#pragma once

#include <variant>
#include <queue>
#include "Resources.h"
#include "BmpReader.h"
#include "TxtReader.h"
#include "Encoder.h"

#include "Overload.h"


/** \class ILoader
 *
 *  \ingroup Encoder
 *
 *  \brief A base interface for a map loader.
 *
 *  load() is a pure virtual method to be overriden by deriving classes.
 *
 *
 *  */
class ILoader {
public:
    /** \brief A pure virtual method to be overriden by deriving classes. */
    virtual void load() = 0;

    /** \brief Enable default constructor. */
    ILoader() = default;
    /** \brief Enable default virtual destructor. */
    virtual ~ILoader() = default;
    /** \brief Enable default copy operations. */
    ILoader(const ILoader&) = default;
    /** \brief Enable default move operations. */
    ILoader(ILoader&&) noexcept = default;
    /** \brief Enable default copy operations. */
    ILoader& operator=(const ILoader&) = default;
    /** \brief Enable default move operations. */
    ILoader& operator=(ILoader&&) noexcept = default;
};


/** \struct Bmp
 *
 *  \ingroup Encoder
 *
 *  \brief Empty struct used to determine file type in MapLoader variant.
 *
 *
 *
 *  */
struct Bmp{};
/** \struct Txt
 *
 *  \ingroup Encoder
 *
 *  \brief Empty struct used to determine file type in MapLoader variant.
 *
 *
 *
 *  */
struct Txt{};


/** \class MapLoader
 *
 *  \ingroup Encoder
 *
 *  \brief Load the map file.
 *
 *  Most operations determined at compile-time.
 *
 *  A file can be either .bmp or .txt.
 *
 *  This is a class template based on a file type.
 *
 *  */
template <typename FileType>
class MapLoader : public ILoader {
public:

    /** \brief Constructs a map loader of an appropriate either Txt or Bmp type.
     *
     *
     * First analyzes the type of FileType, then loads the map.
     *
     *
     * \note Uses C++17 'if constexpr' and std::is_same to determine the type at compile-time.
     *
     *
     *
     * */
    explicit MapLoader(std::string fileName) {
        if constexpr (std::is_same<FileType, Bmp>()) {
            mapReader = BmpReader(fileName);
            encoder   = Encoder<PixelColor>();
        }
        if constexpr (std::is_same<FileType, Txt>()) {
            mapReader = TxtReader(fileName);
            encoder   = Encoder<int>();
        }

        load();
    }

    /** \brief Loads the map data into the #queue.
     *
     * Analyzing the data effectively means counting the Collidable block game entities.
     *
     *
     * \note Uses std::visit with overload hack.
     *
     *
     * */
    void load() override {
        std::visit(overload{
            [&](BmpReader&) { analyzeBmpMapData(); },
            [&](TxtReader&) { analyzeTxtMapData(); },
            [&](std::monostate&) { }
        }, mapReader);

    }

    /** \bief Enable default destructor. */
    virtual ~MapLoader() = default;
    /** \bief Enable default copy operations. */
    MapLoader(const MapLoader&) = default;
    /** \bief Enable default move operations. */
    MapLoader(MapLoader&&) noexcept = default;
    /** \bief Enable default copy operations. */
    MapLoader& operator=(const MapLoader&) = default;
    /** \bief Enable default move operations. */
    MapLoader& operator=(MapLoader&&) noexcept = default;


    /** \brief Retrieve the data.
     *
     * Currently not used, may be re-used in the future.
     *
     * */
    auto& getData() const {
        std::visit(overload{
            [this](BmpReader&)      { return std::get<BmpReader>(mapReader).getData(); },
            [this](TxtReader&)      { return std::get<TxtReader>(mapReader).getData(); },
            [this](std::monostate&) { return std::nullopt; }
        }, mapReader);
    }

    /** \brief Retrieve data queue.
     *
     * @returns std::queue<res::Texture> queue of Textures
     * */
    auto& getQueue() {
        return queue;
    }


    std::variant<std::monostate, Encoder<PixelColor>, Encoder<int>>     encoder; ///< \brief Encoder variant.
    std::variant<std::monostate, BmpReader, TxtReader>                  mapReader; ///< \brief MapReader variant.
private:

    int blocksNum{}; ///< Store the number of collidable blocks.
    std::queue<res::Texture> queue; ///< The queue of textures, FIFO needed when constructing the map to preserve the order.

    /** \brief Counts the number of collidable objects from a **bmp** map data. Inserts them into FIFO queue container.
      *
      * May see improvements in the future.
      *
     * */
    void analyzeBmpMapData() {
        auto& data        = std::get<BmpReader>(mapReader).getData();
        auto& encodedObjs = std::get<Encoder<PixelColor>>(encoder).encodedObjects;

        for (blocksNum = 0; const auto& item : data) {
            switch (encodedObjs.find(item)->second) {
                case Obj::Entity::BlockBlue:
                    queue.push(res::Texture::BlockBlue);
                    ++blocksNum;
                    break;
                case Obj::Entity::BlockYellow:
                    queue.push(res::Texture::BlockYellow);
                    ++blocksNum;
                    break;
                case Obj::Entity::BlockRed:
                    queue.push(res::Texture::BlockRed);
                    ++blocksNum;
                    break;
                case Obj::Entity::BlockGreen:
                    queue.push(res::Texture::BlockGreen);
                    ++blocksNum;
                    break;
                case Obj::Entity::BlockBrown:
                    queue.push(res::Texture::BlockBrown);
                    ++blocksNum;
                    break;
                case Obj::Entity::BlockGray:
                    queue.push(res::Texture::BlockGray);
                    ++blocksNum;
                    break;
                case Obj::Entity::BlockPurple:
                    queue.push(res::Texture::BlockPurple);
                    ++blocksNum;
                    break;
                case Obj::Entity::BlockCrate:
                    queue.push(res::Texture::BlockCrate);
                    ++blocksNum;
                    break;
                case Obj::Entity::Water1:
                    queue.push(res::Texture::Water1);
                    ++blocksNum;
                    break;
                case Obj::Entity::Water2:
                    queue.push(res::Texture::Water2);
                    ++blocksNum;
                    break;
                case Obj::Entity::Sign1:
                    queue.push(res::Texture::Sign1);
                    ++blocksNum;
                    break;
                case Obj::Entity::Sign2:
                    queue.push(res::Texture::Sign2);
                    ++blocksNum;
                    break;
                default:
                    break;
            }
        }
    }

    /** \brief Counts the number of collidable objects from a **txt** map data. Inserts them into FIFO queue container.
      *
      * May see improvements in the future.
      *
     * */
    void analyzeTxtMapData() {
        auto& data        = std::get<TxtReader>(mapReader).getData();
        auto& encodedObjs = std::get<Encoder<int>>(encoder).encodedObjects;

        for (blocksNum = 0; const auto& item : data) {
            switch (encodedObjs.find(item)->second) {
                case Obj::Entity::BlockBlue:
                    queue.push(res::Texture::BlockBlue);
                    ++blocksNum;
                    break;
                case Obj::Entity::BlockYellow:
                    queue.push(res::Texture::BlockYellow);
                    ++blocksNum;
                    break;
                case Obj::Entity::BlockRed:
                    queue.push(res::Texture::BlockRed);
                    ++blocksNum;
                    break;
                case Obj::Entity::BlockGreen:
                    queue.push(res::Texture::BlockGreen);
                    ++blocksNum;
                    break;
                case Obj::Entity::BlockBrown:
                    queue.push(res::Texture::BlockBrown);
                    ++blocksNum;
                    break;
                case Obj::Entity::BlockGray:
                    queue.push(res::Texture::BlockGray);
                    ++blocksNum;
                    break;
                case Obj::Entity::BlockPurple:
                    queue.push(res::Texture::BlockPurple);
                    ++blocksNum;
                    break;
                case Obj::Entity::BlockCrate:
                    queue.push(res::Texture::BlockCrate);
                    ++blocksNum;
                    break;
                case Obj::Entity::Water1:
                    queue.push(res::Texture::Water1);
                    ++blocksNum;
                    break;
                case Obj::Entity::Water2:
                    queue.push(res::Texture::Water2);
                    ++blocksNum;
                    break;
                case Obj::Entity::Sign1:
                    queue.push(res::Texture::Sign1);
                    ++blocksNum;
                    break;
                case Obj::Entity::Sign2:
                    queue.push(res::Texture::Sign2);
                    ++blocksNum;
                    break;
                default:
                    break;
            }
        }
    }
};