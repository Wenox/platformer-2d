#pragma once

#include <variant>
#include <queue>
#include "Resources.h"
#include "BmpReader.h"
#include "TxtReader.h"
#include "Encoder.h"

#include "Overload.h"


class ILoader {
public:
    virtual void load() = 0;

    virtual ~ILoader() = default;
    ILoader() = default;
    ILoader(const ILoader&) = default;
    ILoader(ILoader&&) noexcept = default;
    ILoader& operator=(const ILoader&) = default;
    ILoader& operator=(ILoader&&) noexcept = default;
};

struct Bmp{};
struct Txt{};

template <typename FileType>
class MapLoader : public ILoader {
public:
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

    void load() override {
        std::visit(overload{
            [&](BmpReader&) { analyzeBmpMapData(); },
            [&](TxtReader&) { analyzeTxtMapData(); },
            [&](std::monostate&) { std::cerr << "Monostate\n"; }
        }, mapReader);

    }

    virtual ~MapLoader() = default;
    MapLoader(const MapLoader&) = default;
    MapLoader(MapLoader&&) noexcept = default;
    MapLoader& operator=(const MapLoader&) = default;
    MapLoader& operator=(MapLoader&&) noexcept = default;

    auto getBlocksNum() const {
        return blocksNum;
    }

    auto& getData() const {
        std::visit(overload{
            [this](BmpReader&)      { return std::get<BmpReader>(mapReader).getData(); },
            [this](TxtReader&)      { return std::get<TxtReader>(mapReader).getData(); },
            [this](std::monostate&) { return std::nullopt; }
        }, mapReader);
    }

    auto& getQueue() {
        return queue;
    }


    std::variant<std::monostate, Encoder<PixelColor>, Encoder<int>>     encoder;
    std::variant<std::monostate, BmpReader, TxtReader>                  mapReader;
private:
    int blocksNum{};
    std::queue<res::Texture> queue;

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