/** @file */
#pragma once

#include "ResourceHolder.h"
#include "Resources.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <thread>

/** \class ResourceManager
 *
 * \ingroup myresourcez
 *
 * \brief ResourceManager is a class responsible for managing all kinds of ResourceHolders.
 *
 * Encapsulates TexturesHolder, SoundsHolder and MusicHolder.
 *
 * */

class ResourceManager {
public:
    /** \brief Call loadResources() which may throw.
     *
     * \warning Exits with EXIT_FAILURE on catching an error, because missing resource is a fundamental problem for a game.
     *
     * */
    ResourceManager();

private:
    ResourceHolder<res::Texture, sf::Texture> textures{"../resources/Textures/"}; ///< textures container
    ResourceHolder<res::Sound, sf::SoundBuffer> sounds{"../resources/Sounds/"};   ///< sounds container
    ResourceHolder<res::Music, sf::Music> music{"../resources/Music/"};           ///< music container

    /** \brief Loads all resources, each different resource type uses different thread to handle its type.
     *
     * \warning May throw
     *
     *
     * */
    void loadResources();

    /** \brief Loads all texture resources. May throw. */
    void loadTextures();
    /** \brief Loads all sound resources. May throw. */
    void loadSounds();
    /** \brief Loads all music resources. May throw. */
    void loadMusic();

public:

    /** Retrieve a reference to the textures holder.
     * @returns reference to the textures holder. */
    auto& getTextures() {
        return textures;
    }
    /** Retrieve a reference to the sounds holder.
     * @returns reference to the sounds holder. */
    auto& getSounds() {
        return sounds;
    }
/** Retrieve a reference to the music holder.
     * @returns reference to the music holder. */
    auto& getMusic() {
        return music;
    }
};


