#pragma once

#include <SFML/Audio/SoundBuffer.hpp>
#include "ResourceManager.h"
#include "DefinedResources.h"
#include "ResourceInserter.h"


class ResourcesPool {
public:

    ResourcesPool() {
        loadTextures();
        loadSounds();
    }

    auto& getTextures() {
        return textures;
    }

    auto& getTextures() const {
        return textures;
    }

private:
    ResourceManager<res::Texture, sf::Texture> textures;
    ResourceManager<res::Sound, sf::SoundBuffer> sounds{"../resources/sound/"};

    void loadTextures() {
        textures += ResourceInserter(res::Texture::Wizard, "wizard.png");
        textures.insert(res::Texture::Gray, "gray.png");
        textures.insert(res::Texture::Orange,  "orange.png");
    }

    void loadSounds() {
        sounds.insert(res::Sound::Bullet, "boing.wav");
        sounds.insert(res::Sound::Bing,   "boing_long.wav");
        sounds.insert(res::Sound::Poof,   "poof.wav");
    }
};


