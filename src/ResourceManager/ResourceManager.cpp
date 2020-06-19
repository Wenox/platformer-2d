/** @file */
#include "ResourceManager.h"


ResourceManager::ResourceManager() {
    try {
        loadResources();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        std::exit(EXIT_FAILURE);
    }
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

    /** Player */
    textures.insert(res::Texture::PlayerLeft,  "Player_Left.png");
    textures.insert(res::Texture::PlayerRight, "Player_Right.png");
    textures.insert(res::Texture::Player,      "Player_Standing.png");


    /** Blocks */
    textures.insert(res::Texture::BlockRed,    "Block_Red.png");
    textures.insert(res::Texture::BlockBlue,   "Block_Blue.png");
    textures.insert(res::Texture::BlockBrown,  "Block_Brown.png");
    textures.insert(res::Texture::BlockGray,   "Block_Gray.png");
    textures.insert(res::Texture::BlockGreen,  "Block_Green.png");
    textures.insert(res::Texture::BlockPurple, "Block_Purple.png");
    textures.insert(res::Texture::BlockYellow, "Block_Yellow.png");
    textures.insert(res::Texture::BlockCrate,  "Block_Crate.png");
    textures.insert(res::Texture::Sign1,       "Block_Sign_1.png");
    textures.insert(res::Texture::Sign2,       "Block_Sign_2.png");
    textures.insert(res::Texture::Water1,      "Block_Water_1.png");
    textures.insert(res::Texture::Water2,      "Block_Water_2.png");


    /** Special */
    textures.insert(res::Texture::Spike,       "Spike.png");
    textures.insert(res::Texture::Objective,   "Objective.png");
    textures.insert(res::Texture::Heart,       "Heart.png");
    textures.insert(res::Texture::HeartEmpty,  "Heart_Empty.png");


    /** Large textures */
    textures.insert(res::Texture::GameLost,    "Texture_Game_Lost.png");
    textures.insert(res::Texture::GameWon,     "Texture_Game_Won.png");
    textures.insert(res::Texture::BgGame,      "Texture_Game_Background.jpg");
    textures.insert(res::Texture::BgAbout,     "Texture_About.png");


    /** Corners in the Options menu */
    textures.insert(res::Texture::OptionsLeftTopCorner,  "Corner_Left_Top.png");
    textures.insert(res::Texture::OptionsLeftBotCorner,  "Corner_Left_Bot.png");
    textures.insert(res::Texture::OptionsRightBotCorner, "Corner_Right_Top.png");
    textures.insert(res::Texture::OptionsRightTopCorner, "Corner_Right_Bot.png");
}

void ResourceManager::loadSounds() {
    sounds += ResourceInserter(res::Sound::BtnHover, "Button_Hover.ogg");
    sounds += ResourceInserter(res::Sound::Collect,  "Collect.wav");
    sounds += ResourceInserter(res::Sound::Death,    "Death.wav");
    sounds += ResourceInserter(res::Sound::WinGame,  "Win.ogg");
}

void ResourceManager::loadMusic() {
//    music.insert(res::Music::Background, "Background.ogg");
}