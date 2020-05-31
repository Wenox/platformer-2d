#pragma once

#include <variant>
#include <queue>
#include <ResourceManager/Resources.h>
#include "BmpReader.h"
#include "TxtReader.h"
#include "Encoder.h"


class ILoader {
public:
    virtual void load() = 0;

    virtual ~ILoader() = default;
    ILoader() = default;
    ILoader(const ILoader&) = default;
    ILoader(ILoader&&) = default;
    ILoader& operator=(const ILoader&) = default;
    ILoader& operator=(ILoader&&) = default;
};


struct Bmp {};
struct Txt {};


template<class... Ts> struct overload : Ts... { using Ts::operator()...; };
template<class... Ts> overload(Ts...) -> overload<Ts...>;


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
            [&](BmpReader&) {
                /** Analyzer */
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
                }
            }

            },
            [&](TxtReader&) {
                /** Analyzer */
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
                }
            }
            },
            [&](std::monostate&) { std::cerr << "Not yet constructed\n"; }
        }, mapReader);

    }

    virtual ~MapLoader() = default;
    MapLoader(const MapLoader&) = default;
    MapLoader(MapLoader&&) = default;
    MapLoader& operator=(const MapLoader&) = default;
    MapLoader& operator=(MapLoader&&) = default;

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

public:
    int blocksNum{};
    std::variant<std::monostate, BmpReader, TxtReader>                  mapReader;
    std::variant<std::monostate, Encoder<PixelColor>, Encoder<int>>     encoder;
    std::queue<res::Texture> queue;
};