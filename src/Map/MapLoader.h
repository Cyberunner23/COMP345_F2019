#pragma once

#include <fstream>

#include "Utils/SerializationUtils.hpp"

#include "Map/Map.h"

struct SerializedMap
{
    SerializedMap()
    {
        Continents = new std::vector<std::string>();
        Countries = new std::vector<std::string>();
        CountryContinentMapping = new std::map<std::string, std::string>();
        CountryConnections = new std::vector<std::pair<std::string, std::string>>();
    }

    std::vector<std::string>* Continents;
    std::vector<std::string>* Countries;
    std::map<std::string, std::string>* CountryContinentMapping;
    std::vector<std::pair<std::string, std::string>>* CountryConnections;

    SERIALIZE(archive,
    {
        archive & NameValuePair("Continents", *Continents);
        archive & NameValuePair("Countries", *Countries);
        archive & NameValuePair("CountryContinentMapping", *CountryContinentMapping);
        archive & NameValuePair("CountryConnections", *CountryConnections);
    })
};
SERIALIZE_IMPLEMENT_STREAM(SerializedMap);

class MapLoader
{
public:
    Map* loadMap(std::string const& filePath);
    void saveMap(std::string const& filePath, SerializedMap& map);
};
