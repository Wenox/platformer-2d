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


#if (__cplusplus == 202002L)
template <typename T>
    concept Mappable = std::strict_weak_order<std::less<T>, T, T>;
#endif


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

template <typename T, typename... Args>
ResourceInserter(T, std::string_view, Args... args) -> ResourceInserter<T, Args...>;
