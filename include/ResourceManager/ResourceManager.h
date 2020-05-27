#pragma once

#include "ResourceHolder.h"
#include "Resources.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <thread>


class ResourceManager {
public:
    ResourceManager();

private:
    ResourceHolder<res::Texture, sf::Texture> textures;
    ResourceHolder<res::Sound, sf::SoundBuffer> sounds{"../resources/sound/"};
    ResourceHolder<res::Music, sf::Music> music;

    void loadResources();

    void loadTextures();
    void loadSounds();
    void loadMusic();

public:
    auto& getTextures() {
        return textures;
    }

    auto& getSounds() {
        return sounds;
    }

    auto& getMusic() {
        return music;
    }
};


