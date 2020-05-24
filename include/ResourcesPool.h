#pragma once

#include <SFML/Audio/SoundBuffer.hpp>
#include "ResourceManager.h"

namespace res {
    enum class Texture {
        Gray,
        Green,
        Orange,
        Wizard
    };

    enum class Sound {
        Bullet,
        Poof,
        Bing
    };
}

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
        textures.insert(res::Texture::Wizard, "wizard.png");
        textures.insert(res::Texture::Orange, "gray.png");
        textures.insert(res::Texture::Green,  "green.png");
    }

    void loadSounds() {
        sounds.insert(res::Sound::Bullet, "boing.wav");
        sounds.insert(res::Sound::Bing,   "boing_long.wav");
        sounds.insert(res::Sound::Poof,   "poof.wav");
    }
};


