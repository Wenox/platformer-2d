#pragma once

#include <iostream>
#include <memory>
#include <unordered_map>
#include "ResourceInserter.h"

#include <concepts>
#include <type_traits>
#include <SFML/Audio/Music.hpp>


template <typename Key, typename Resource>
#if (__cplusplus == 202002L)
    requires Mappable<Key>
#endif
class ResourceHolder {
public:

    explicit ResourceHolder(std::string resourcesDir = "../resources/")
            : resourcesDir{std::move(resourcesDir)}
    {}

    template <typename... Args>
    void insert(const Key& key, std::string_view fileName, Args&&... args) {
        auto resPtr = std::make_unique<Resource>();

        bool loaded{};
        if constexpr (std::is_same<Resource, sf::Music>()) {
            loaded = resPtr->openFromFile(resourcesDir + fileName.data(), std::forward<Args>(args)...);
        } else {
            loaded = resPtr->loadFromFile(resourcesDir + fileName.data(), std::forward<Args>(args)...);
        }

        if (!loaded) {
            msgErrorLoading(fileName);
            ///* todo: possibly "throw ErrorLoadingResource" here */
            return;
        }
        resources.emplace(key, std::move(resPtr));
    }

    Resource& get(const Key& key) const {
        if (auto resource = resources.find(key); resource != std::end(resources)) {
            return *(resource->second);
        } throw std::invalid_argument{"No such resource id."};
    }

    bool has(const Key& key) const {
        return get(key) != nullptr;
    }

    void erase(const Key& key) noexcept {
        if (auto found = resources.find(key); found != std::end(resources)) {
            resources.erase(key);
        }
    }

    void eraseAll() noexcept {
        resources.clear();
    }

private:
    std::string resourcesDir;
    std::unordered_map<Key, std::unique_ptr<Resource>> resources;

public:

    const Resource& operator[](const Key& key) const {
        return get(key);
    }

    Resource& operator[](const Key& key) {
        return get(key);
    }

    auto& getResources() const {
        return resources;
    }

    auto& getResourcesDir() const {
        return resourcesDir;
    }

    void setResourcesDir(std::string newPath) {
        resourcesDir = std::move(newPath);
    }

    template <typename... Args>
    ResourceHolder& operator+=(const ResourceInserter<Key, Args...>& inserter) {

        if constexpr (sizeof...(Args) == 0) {
            insert(std::move(inserter.key),
                   std::move(inserter.fileName));
        } else {
            insert(std::move(inserter.key),
                   std::move(inserter.fileName),
                   std::move(std::get<Args...>(inserter.args)));
        }

        return *this;
    }

    template <typename... Args>
    ResourceHolder& operator+=(ResourceInserter<Key, Args...>&& inserter) {

        if constexpr (sizeof...(Args) == 0) {
            insert(std::move(inserter.key),
                   std::move(inserter.fileName));
        } else {
            insert(std::move(inserter.key),
                   std::move(inserter.fileName),
                   std::move(std::get<Args...>(inserter.args)));
        }

        return *this;
    }

private:
    void msgErrorLoading(std::string_view fileName) {
         std::cerr << "Failed loading resource: "
                      "{ Type: \""  << typeid(Resource).name()<< "\", File name: \"" << fileName << "\" }\n";
    }
};
