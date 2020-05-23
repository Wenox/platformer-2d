#pragma once


#include <map>
#include <string>
#include <SFML/Graphics/Texture.hpp>
#include <iostream>

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
        sf::Texture t;
        if (!t.loadFromFile(s)) {
            std::cerr << "Cannot load: " << s << std::endl;
        }
        textures.emplace(s, t);
    }

    sf::Texture& get(const std::string& id) {
        if (auto resource = textures.find(id); resource != std::end(textures)) {
            return (*resource).second;
        } throw std::invalid_argument{"No such resource id: " + id};
    }


    void print() {
        for (auto [key, val] : textures) {
            std::cout << "Resource: " << key << std::endl;
        }
    }

private:
    std::unordered_map<std::string, sf::Texture> textures;
};


