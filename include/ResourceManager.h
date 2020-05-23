#pragma once


#include <map>
#include <string>
#include <SFML/Graphics/Texture.hpp>
#include <iostream>
#include <memory>

class ResourceManager {
public:
    ResourceManager() {
        this->insert("../resources/wizard.png");
        this->insert("../resources/gray.png");
        this->insert("../resources/orange.png");

        auto res1 = this->get("../resources/wizard.png");
        auto res2 = this->get("../resources/gray.png");
        auto res3 = this->get("../resources/orange.png");
    }

    void insert(const std::string& s) {
        std::unique_ptr<sf::Texture> t(new sf::Texture);
        if (!t->loadFromFile(s)) {
            std::cerr << "Cannot load: " << s << std::endl;
        }
        textures.emplace(s, move(t));
    }

    sf::Texture& get(const std::string& id) {
        if (auto resource = textures.find(id); resource != std::end(textures)) {
            return *(resource->second);
        } throw std::invalid_argument{"No such resource id: " + id};
    }


    void print() {
        for (const auto& resource : textures) {
            std::cout << "Resource: " << resource.first << std::endl;
        }
    }

private:
    std::unordered_map<std::string, std::unique_ptr<sf::Texture>> textures;
};


