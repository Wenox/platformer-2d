#include "ResourceManager.h"


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
    textures.insert(res::Texture::BlockRed,    "Block_Type1_Red.png");
    textures.insert(res::Texture::BlockBlue,   "Block_Type1_Blue.png");
    textures.insert(res::Texture::BlockBrown,  "Block_Type1_Brown.png");
    textures.insert(res::Texture::BlockGray,   "Block_Type1_Gray.png");
    textures.insert(res::Texture::BlockGreen,  "Block_Type1_Green.png");
    textures.insert(res::Texture::BlockPurple, "Block_Type1_Purple.png");
    textures.insert(res::Texture::BlockYellow, "Block_Type1_Yellow.png");
    textures.insert(res::Texture::Wizard,  "wizard2.png");
    textures.insert(res::Texture::Objective,  "Door_Type1_Yellow_Closed.png");
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