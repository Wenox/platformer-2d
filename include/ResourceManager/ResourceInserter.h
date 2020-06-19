/** @file */

#pragma once

#include <utility>


#if (__cplusplus == 202002L)
    template <typename Key>
    concept Mappable = std::strict_weak_order<std::less<Key>, Key, Key>;
#endif


/** \class ResourceInserter
 *
 *  \ingroup myresourcez
 *
 * \brief A proxy class used to handle 2+ arguments in operator+=, which takes only 1 argument.
 *
 * Uses Mappable custom concept (C++20).
 *
 * \note
 * There are two ways to insert new resources into:
 *  ResourceHolder<Key, Resource> resources;
 *
 *  1:
 *  resources.insert(key, args...);
 *  2:
 *  resources += ResourceInserter(key, args...);
 *
 *  ResourceInserter is a proxy class for operator+=,
 *  which is an alternative way of inserting resources
 *
 *  */
template <typename Key, typename... Args>
#if (__cplusplus == 202002L)
    requires Mappable<Key>
#endif
class ResourceInserter {
public:
    explicit ResourceInserter(Key key, std::string_view fileName, Args... args)
            : key{std::move(key)}
            , fileName{fileName}
            , args{std::move<Args>(args)...}
    {
    }
    Key key;
    std::string fileName;
    std::tuple<Args...> args;
};

/** \brief Deduction guide */
template <typename T, typename... Args>
ResourceInserter(T, std::string_view, Args... args) -> ResourceInserter<T, Args...>;
