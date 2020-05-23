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

    void insert(const Key& key) {
        std::unique_ptr<Resource> resPtr(new Resource);
        if (!resPtr->loadFromFile(key)) {
            std::cerr << "Cannot load: " << key << std::endl;
            ///* todo: default texture */
        }
        resources.emplace(key, std::move(resPtr));
    }

    Resource& get(const Key& key) const {
        if (auto resource = resources.find(key); resource != std::end(resources)) {
            return *(resource->second);
        } throw std::invalid_argument{"No such resource id: " + key};
    }


    void print() {
        for (const auto& resource : resources) {
            std::cout << "Resource: " << resource.first << std::endl;
        }
    }

private:
    std::unordered_map<Key, std::unique_ptr<Resource>> resources;
};


