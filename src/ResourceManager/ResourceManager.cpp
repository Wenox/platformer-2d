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

    textures.insert(res::Texture::PlayerLeft,  "player_left.png");
    textures.insert(res::Texture::PlayerRight,  "player_right.png");
    textures.insert(res::Texture::Player,  "player_standing.png");

    textures.insert(res::Texture::Objective,  "Door_Type1_Yellow_Closed.png");

    textures.insert(res::Texture::Heart,  "heart.png");
    textures.insert(res::Texture::HeartEmpty,  "heart-empty.png");

    textures.insert(res::Texture::Spike,  "spike.png");

    textures.insert(res::Texture::BgClouds, "clouds1.jpg");

    textures.insert(res::Texture::BgPaused, "pausedBg.png");
}

void ResourceManager::loadSounds() {
    sounds += ResourceInserter(res::Sound::Bing, "boing.wav");
    sounds.insert(res::Sound::Bullet,   "boing_long.wav");
    sounds.insert(res::Sound::Death,   "death.wav");
}

void ResourceManager::loadMusic() {
//    music.insert(res::Music::Ambient, "boing.wav");
//    music.insert(res::Music::Ambient, "boing_bad.wav");
}