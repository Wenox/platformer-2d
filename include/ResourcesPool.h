#pragma once

#include "ResourceManager.h"

namespace obj {
    enum class Texture {
        Gray,
        Green,
        Orange,
        Wizard
    };
}

class ResourcesPool {
public:
    ResourcesPool() {
        loadTextures();
    }

    auto& getTextures() {
        return textures;
    }

    auto& getTextures() const {
        return textures;
    }

private:
    ResourceManager<obj::Texture, sf::Texture> textures;
    void loadTextures() {
        textures.insert(obj::Texture::Wizard, "../resources/wizard.png");
        textures.insert(obj::Texture::Orange, "../resources/gray.png");
        textures.insert(obj::Texture::Green, "../resources/green.png");
    }
};


