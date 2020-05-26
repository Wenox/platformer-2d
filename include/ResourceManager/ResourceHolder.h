#pragma once

#include <iostream>
#include <memory>
#include <unordered_map>
#include "ResourceInserter.h"

#include <concepts>
#include <type_traits>


#if (__cplusplus == 202002L)
    template <typename T>
    concept Mappable = std::strict_weak_order<std::less<T>, T, T>;
#endif


template <typename Key, typename Resource>
#if (__cplusplus == 202002L)
    requires Mappable<T>
#endif
class ResourceHolder {
public:

    explicit ResourceHolder(std::string resourcesDir = "../resources/")
            : resourcesDir{std::move(resourcesDir)}
    {}

    template <typename... Args>
    void insert(const Key& key, Args&&... args) {
        auto resPtr = std::make_unique<Resource>();
        if (!resPtr->loadFromFile(resourcesDir + std::forward<Args>(args)...)) {
            msgErrorLoading(args...);
            ///* todo: should I e.g. "throw ErrorLoadingResource" here? */
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

    void eraseAll() {
        resources.clear();
    }

private:
    std::string resourcesDir;
    std::unordered_map<Key, std::unique_ptr<Resource>> resources;

public:
    template <typename... Args>
    ResourceHolder& operator+=(const ResourceInserter<Key, Args...>& inserter) {
        insert(std::move(inserter.key), std::move(std::get<Args>(inserter.args)...));
        return *this;
    }

    inline const Resource& operator[](const Key& key) const {
        return get(key);
    }

    inline Resource& operator[](const Key& key) {
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

private:
    template <typename... Args>
    void msgErrorLoading(const Args&... args) {
         std::cerr << "Failed loading resource: { Type: \"" << typeid(Resource).name()<< "\", File name: \"";
        (std::cerr << ... << args) << "\" }" << std::endl;
    }
};