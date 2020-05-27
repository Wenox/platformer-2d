#include "ResourceManager/ResourceManager.h"

ResourceManager::ResourceManager() {
    loadResources();
}

void ResourceManager::loadResources() {
    std::thread t1(&ResourceManager::loadTextures, this);
    std::thread t2(&ResourceManager::loadSounds, this);
    t1.join();
    t2.join();
}

void ResourceManager::loadTextures() {
    textures.insert(res::Texture::Wizard, "wizard.png");
    textures.insert(res::Texture::Wizard, "wizard.png");
    textures.insert(res::Texture::Wizard, "wizard.pngg");
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
    sounds.insert(res::Sound::Bing,   "boing_long.wav");
}