#pragma once

#include "ResourceManager.h"


class ResourcesPool {
public:
    ResourcesPool() {
        loadTextures();
    }

    auto& getTextures() {
        return textures;
    }

private:
    ResourceManager<std::string, sf::Texture> textures;
    void loadTextures() {
        textures.insert("../resources/wizard.png");
        textures.insert("../resources/orange.png");
        textures.insert("../resources/green.png");
    }
};


