#pragma once

#include <map>
#include <string>
#include <SFML/Graphics/Texture.hpp>
#include <iostream>
#include <memory>


template <typename Key, typename Resource>
class ResourceManager {
public:
    template <typename... Args>
    void insert(const Key& key, Args&&... args) {
        std::unique_ptr<Resource> resPtr(new Resource);
        if (!resPtr->loadFromFile(std::forward<Args>(args)...)) {
            errorLoading(std::forward<Args>(args)...);
        }
        resources.emplace(key, std::move(resPtr));
    } ///* todo: use default resource(?) or throw exception */

    Resource& get(const Key& key) const {
        if (auto resource = resources.find(key); resource != std::end(resources)) {
            return *(resource->second);
        } throw std::invalid_argument{"No such resource id."};
    }

private:
    std::unordered_map<Key, std::unique_ptr<Resource>> resources;

    template <typename... Args>
    void errorLoading(Args&&... args) {
         std::cerr << "Failed loading resource: { Type: \"" << typeid(Resource).name()<< "\", File name: \"";
        (std::cerr << ... << std::forward<Args>(args)) << "\" }" << std::endl;
    }
};
