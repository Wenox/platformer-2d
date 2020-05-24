#pragma once

#include <map>
#include <string>
#include <SFML/Graphics/Texture.hpp>
#include <iostream>
#include <memory>
#include "Resources.h"
#include "ResourceInserter.h"


template <typename Key, typename Resource>
class ResourceHolder {
public:
    explicit ResourceHolder(std::string resourcesPath = "../resources/")
        : resourcesPath{std::move(resourcesPath)}
    {}

    template <typename... Args>
    void insert(const Key& key, Args&&... args) {
        std::unique_ptr<Resource> resPtr(new Resource);
        if (!resPtr->loadFromFile(resourcesPath + std::forward<Args>(args)...)) {
            msgErrorLoading(std::forward<Args>(args)...);
            ///* todo: should I e.g. "throw ErrorLoadingResource" here? */
        }
        resources.emplace(key, std::move(resPtr));
    }

    template <typename... Args>
    ResourceHolder& operator+=(const ResourceInserter<Key, Args...>& inserter) {
        insert(std::move(inserter.key), std::move(std::get<Args>(inserter.args)...));
        return *this;
    }

    Resource& get(const Key& key) const {
        if (auto resource = resources.find(key); resource != std::end(resources)) {
            return *(resource->second);
        } throw std::invalid_argument{"No such resource id."};
    }

    inline const Resource& operator[](const Key& key) const {
        return get(std::move(key));
    }

    inline Resource& operator[](const Key& key) {
        return get(std::move(key));
    }

    void erase(const Key& key) noexcept {
        if (auto found = resources.find(key); found != std::end(resources)) {
            resources.erase(key);
        }
    }

    void eraseAll() {
        resources.clear();
    }

    auto& getResourcesPath() const {
        return resourcesPath;
    }

    auto& getResources() const {
        return resources;
    }

    void setResourcesPath(std::string newPath) {
        resourcesPath = std::move(newPath);
    }

private:
    std::string resourcesPath;
    std::unordered_map<Key, std::unique_ptr<Resource>> resources;

    template <typename ... Args>
    void msgErrorLoading(Args ... args) {
         std::cerr << "Failed loading resource: { Type: \"" << typeid(Resource).name()<< "\", File name: \"";
        (std::cerr << ... << args) << "\" }" << std::endl;
    }
};
