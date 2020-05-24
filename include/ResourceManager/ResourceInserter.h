#pragma once

#include <utility>

/** There are two ways to insert new resources into:
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
class ResourceInserter {
public:
    explicit ResourceInserter(Key&& key, Args&&... args)
            : key{std::forward<Key>(key)}
            , args{std::forward<Args>(args)...}
    {}

    Key key;
    std::tuple<Args...> args;
};

template <typename T, typename... Args>
ResourceInserter(T&&, Args&&... args) -> ResourceInserter<T, Args...>;
