#pragma once

#include <map>

template<typename K, typename V>
bool findByValue(K& keyFound, std::map<K, V>& map, V value)
{
    for (auto& pair : map)
    {
        if (pair.second == value)
        {
            keyFound = pair.first;
            return true;
        }
    }

    return false;
}