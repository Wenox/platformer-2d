#include "ResourceManager/ResourceManager.h"

ResourceManager::ResourceManager() {
    loadTextures();
    loadSounds();
}

void ResourceManager::loadTextures() {
    textures.insert(res::Texture::Wizard, "wizard.png");
    textures.insert(res::Texture::Gray,   "gray.png");
    textures.insert(res::Texture::Orange, "orange.png");
}

void ResourceManager::loadSounds() {
    sounds += ResourceInserter(res::Sound::Bullet, "boing.wav");
    sounds += ResourceInserter(res::Sound::Bing,   "boing_long.wav");
    sounds += ResourceInserter(res::Sound::Poof,   "poof.wav");
}