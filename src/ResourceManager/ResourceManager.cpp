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
    textures.insert(res::Texture::BlockCrate, "crate.png");

    textures.insert(res::Texture::Sign1, "Sign_1.png");
    textures.insert(res::Texture::Sign2, "Sign_2.png");
    textures.insert(res::Texture::Water1, "water1.png");
    textures.insert(res::Texture::Water2, "water2.png");

    textures.insert(res::Texture::PlayerLeft,  "player_left.png");
    textures.insert(res::Texture::PlayerRight,  "player_right.png");
    textures.insert(res::Texture::Player,  "player_standing.png");

    textures.insert(res::Texture::Objective,  "Door_Type1_Yellow_Closed.png");

    textures.insert(res::Texture::Heart,  "heart.png");
    textures.insert(res::Texture::HeartEmpty,  "heart-empty.png");

    textures.insert(res::Texture::Spike,  "spike.png");

    textures.insert(res::Texture::BgGame, "violet.jpg");

    textures.insert(res::Texture::BgPaused, "pausedBg2.png");
    textures.insert(res::Texture::BgOptions, "test8.png");


    textures.insert(res::Texture::OptionsLeftTopCorner, "corner-left-top.png");
    textures.insert(res::Texture::OptionsLeftBotCorner, "corner-left-bot.png");
    textures.insert(res::Texture::OptionsRightBotCorner, "corner-right-bot.png");
    textures.insert(res::Texture::OptionsRightTopCorner, "corner-right-top.png");

    textures.insert(res::Texture::GameOver, "gameOver2.png");
    textures.insert(res::Texture::GameWon, "gameWon.png");
}

void ResourceManager::loadSounds() {
    sounds += ResourceInserter(res::Sound::Bing, "boing.wav");
    sounds.insert(res::Sound::Bullet,   "boing_long.wav");
    sounds.insert(res::Sound::Death,   "death.wav");
}

void ResourceManager::loadMusic() {
//    music.insert(res::Music::Arcade, "MaquinasOutpost2.ogg");
}