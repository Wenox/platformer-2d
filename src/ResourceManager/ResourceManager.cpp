#include "ResourceManager/ResourceManager.h"

ResourceManager::ResourceManager() {
    loadResources();
}

void ResourceManager::loadResources() {
    std::thread t1(&ResourceManager::loadTextures, this);
    std::thread t2(&ResourceManager::loadSounds, this);
    std::thread t3(&ResourceManager::loadMusic, this);
    t1.join();
    t2.join();
    t3.join();
}

void ResourceManager::loadTextures() {
    textures.insert(res::Texture::Wizard, "wizard.png");
    textures.insert(res::Texture::Wizard, "wizard.png");
    textures.insert(res::Texture::Wizard, "wizard.png");
    textures.insert(res::Texture::Gray,   "gray.png");
    textures.insert(res::Texture::Gray,   "gray.png");
    textures.insert(res::Texture::Orange, "orange.png");
    textures.insert(res::Texture::Gray,   "gray.png");
    textures.insert(res::Texture::Wizard, "wizard.png");
    textures.insert(res::Texture::Orange, "orange.png");
    textures.insert(res::Texture::Orange, "orange.png");
    textures.insert(res::Texture::Gray,   "gray.png");
    textures.insert(res::Texture::Orange, "orange.png");
    textures.insert(res::Texture::Orange, "orange.png");
    textures.insert(res::Texture::Orange, "orange.png");
}

void ResourceManager::loadSounds() {
    sounds += ResourceInserter(res::Sound::Bullet, "boing.wav");
    sounds += ResourceInserter(res::Sound::Bullet, "boing.wav");
    sounds += ResourceInserter(res::Sound::Bullet, "boing.wav");
    sounds.insert(res::Sound::Bing,   "boing_long.wav");
}

void ResourceManager::loadMusic() {
//    music.insert(res::Music::Ambient, "boing.wav");
//    music.insert(res::Music::Ambient, "boing_bad.wav");
}