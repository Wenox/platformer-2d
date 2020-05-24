#pragma once

#include "ResourceHolder.h"
#include "Resources.h"
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <thread>


class ResourceManager {
public:
    ResourceManager();

private:
    ResourceHolder<res::Texture, sf::Texture> textures;
    ResourceHolder<res::Sound, sf::SoundBuffer> sounds{"../resources/sound/"};

    void loadResources();

    void loadTextures();
    void loadSounds();

public:
    auto& getTextures() {
        return textures;
    }

    auto& getSounds() {
        return sounds;
    }
};


