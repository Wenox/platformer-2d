#pragma once

#include <map>
#include <string>
#include <SFML/Graphics/Texture.hpp>
#include <iostream>
#include <memory>


template <typename Key, typename Resource>
class ResourceManager {
public:
    ResourceManager() {
    }

    template <typename ... Args>
    void insert(const Key& key, Args&& ... args) {
        std::unique_ptr<Resource> resPtr(new Resource);
        if (not resPtr->loadFromFile(std::forward<Args>(args)...)) {
            std::cerr << "Cannot load a resource: " << typeid(Key).name() << std::endl;
            ///* todo: default texture */
        }
        resources.emplace(key, std::move(resPtr));
    }

    Resource& get(const Key& key) const {
        if (auto resource = resources.find(key); resource != std::end(resources)) {
            return *(resource->second);
        } throw std::invalid_argument{"No such resource id."};
    }

private:
    std::unordered_map<Key, std::unique_ptr<Resource>> resources;
};
