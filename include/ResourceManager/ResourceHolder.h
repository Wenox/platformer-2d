/** @file */

/** @defgroup myresourcez Resources
 *  Classes responsible for loading, storing and retrieving the external resources.
 *  @{
 */

 /**
 *
 * @} */ // end of group1

#pragma once

#include <iostream>
#include <memory>
#include "ResourceInserter.h"
#include <SFML/Audio/Music.hpp>
#include <iomanip>
#include <concepts>


/** \class MissingResource
 *
 * \ingroup myresourcez
 *
 * \brief Meaningful response error when resource of given type was missing.
 *
 * */

template <typename Resource>
class MissingResource : public std::exception {
    std::string msg{}; ///< Message to be returned

    /** \brief Make a meaningful error-message using typeid of Resource.
     *
     * \note
     * The message: "Failed loading resource: "
                    "{ Type: "    + std::string(typeid(Resource).name()) + ", "
                    "File name: " + fileName.data()                      + " }";
     *
     * */
    static std::string initMsg(std::string_view fileName) {
        return "Failed loading resource: "
               "{ Type: "    + std::string(typeid(Resource).name()) + ", "
               "File name: " + fileName.data()                      + " }";
    }

public:
    /** \brief Enable default constructor. */
    MissingResource() = default;
    /** brief Builds up meaningufl error message based on fileName and Resource type. */
    MissingResource(std::string_view fileName) : msg{initMsg(fileName)}
    {}

    /** \brief Overriden what() method used in catch block, displaying full error message. */
    const char* what() const noexcept override {
        return msg.data();
    }
};


/** \class ResourceHolder
 *
 * \ingroup myresourcez
 *
 * \brief A generic ResourceHolder storing resources of type Resource, accessed by Key.
 *
 * Custom Mappable concept is used only if C++20 flag is enabled.
 *
 * ResourceHolder has a 'if constexpr method branch specialization' if the Reosurce is sf::Music.
 *
 * Uses Arguments parameter pack to suit future needs (number of arguments in insert() method may vary).
 *
 * \note Resources can be inserted with insert() or operator+=.
 * \note Resources can be accessed with get() or operator[].
 *
 *
 * */
template <typename Key, typename Resource>
#if (__cplusplus == 202002L)
requires Mappable<Key> ///< Uses Mappable concept only if C++20
#endif
class ResourceHolder {
    std::unordered_map<Key, std::unique_ptr<Resource>> resources;
    std::string resourcesDir;

public:

    /** \brief  Constructs an empty ResourceHolder with a given resourceDir root.
     *
     * @param resourcesDir resources root directory
     *
     * ResourceDir defaults to "../resources/".
     * */
    explicit ResourceHolder(std::string_view resourcesDir = "../resources/")
            : resourcesDir{std::move(resourcesDir)}
    {}

    /** \brief Insert a resource of type Resource to a map.
     *
     * @param key A key stored as a key in map, needs to be remembered to retrieve the resource.
     * @param fileName A file path to the Resource.
     * @param args Optional parameter pack, could be used in e.g. sf::shader class in the future.
     *
     * sf::Music has slightly incompatible interface as opposed to other resources, so 'if constexpr' is evaluated.
     * */
    template <typename... Args>
    void insert(const Key& key, std::string_view fileName, Args&&... args) {
        auto resPtr = std::make_unique<Resource>();

        bool loaded{};
        if constexpr (std::is_same<Resource, sf::Music>()) {
            loaded = resPtr->openFromFile(resourcesDir + fileName.data(), std::forward<Args>(args)...);
        } else {
            loaded = resPtr->loadFromFile(resourcesDir + fileName.data(), std::forward<Args>(args)...);
        }

        if (!loaded) {
            throw MissingResource<Resource>(fileName);
        }
        resources.emplace(key, std::move(resPtr));
    }

    /** \brief Retrieves a reference to an existing resource found by a given ID.
     *
     * @param key Resource identifier.
     * @returns Resource& a reference to the found, existing resource.
     *
     * May throw.
     * */
    Resource& get(const Key& key) const {
        if (auto resource = resources.find(key); resource != std::end(resources)) {
            return *(resource->second);
        } throw std::invalid_argument{"No such resource id."};
    }

    /** \brief Check if a ResourceHolder has a given key stored.
     *
     * @param key The key to be checked if it is already stored.
     * @returns Is they key already stored?
     *
     * */
    bool has(const Key& key) const {
        return get(key) != nullptr;
    }

    /** \brief Erase a Resource found by a given key.
     *
     * @param key The key to be used to find a Resource to be erased.
     *
     *
     * */
    void erase(const Key& key) noexcept {
        if (auto found = resources.find(key); found != std::end(resources)) {
            resources.erase(key);
        }
    }

    /** \brief Erase all existing resources within this ResourceHolder. */
    void eraseAll() noexcept {
        resources.clear();
    }

public:

    /** Use operator[] alternatively to retrieve a resource.
     * @param key to be found.
     * @returns Resource found by a given key.
     *
     * Const version. */
    const Resource& operator[](const Key& key) const {
        return get(key);
    }
    /** Use operator[] alternatively to retrieve a resource.
     * @param key to be found.
     * @returns Resource found by a given key.
     *
     * Non-const version. */
    Resource& operator[](const Key& key) {
        return get(key);
    }

    /** \brief Retrieve all resources.
     * @returns a reference to all resources. */
    auto& getResources() const {
        return resources;
    }
    /** \brief Retrieve resources root directory.
     * @returns a reference to #resourcesDir. */
    auto& getResourcesDir() const {
        return resourcesDir;
    }

    /** \brief Set the $resourceDir# to a given new directory.
     * @param newPath new directory to be set
     * */
    void setResourcesDir(std::string newPath) {
        resourcesDir = std::move(newPath);
    }

    /** \brief Use operator+= alternatively to insert() method.
     *
     * @param inserter const reference to a ResourceInserter<Key, Args...> proxy class/
     * @returns a reference to a newly stored resource.
     *
     *  Uses Proxy pattern to make operator+= compatible with 2 parameters.
     *
     *  \note Const lvalue reference version.
     */
    template <typename... Args>
    ResourceHolder& operator+=(const ResourceInserter<Key, Args...>& inserter) {

        if constexpr (sizeof...(Args) == 0) {
            insert(std::move(inserter.key),
                   std::move(inserter.fileName));
        } else {
            insert(std::move(inserter.key),
                   std::move(inserter.fileName),
                   std::move(std::get<Args...>(inserter.args)));
        }

        return *this;
    }

    /** \brief Use operator+= alternatively to insert() method.
     *
     * @param inserter rvalue of a ResourceInserter<Key, Args...> proxy class/
     * @returns a reference to a newly stored resource.
     *
     *  Uses Proxy pattern to make operator+= compatible with 2 parameters.
     *
     *  \note Rvalue reference version.
     */
    template <typename... Args>
    ResourceHolder& operator+=(ResourceInserter<Key, Args...>&& inserter) {

        if constexpr (sizeof...(Args) == 0) {
            insert(std::move(inserter.key),
                   std::move(inserter.fileName));
        } else {
            insert(std::move(inserter.key),
                   std::move(inserter.fileName),
                   std::move(std::get<Args...>(inserter.args)));
        }

        return *this;
    }

private:

};
