#pragma once

#include <fstream>

#include "Utils/SerializationUtils.hpp"

#include "Map/Map.h"

struct CountryConnection
{
    CountryConnection(std::string c1, std::string c2, bool isWaterConnection)
    {
        C1 = new std::string(c1);
        C2 = new std::string(c2);
        IsWaterConnection = new bool(isWaterConnection);
    }

    CountryConnection() : CountryConnection("0", "0", false) {}

    std::string* C1;
    std::string* C2;
    bool* IsWaterConnection;

    SERIALIZE(archive,
    {
        archive & NameValuePair("C1", *C1);
        archive & NameValuePair("C2", *C2);
        archive & NameValuePair("IsWaterConnection", *IsWaterConnection);
    })
};
SERIALIZE_IMPLEMENT_STREAM(CountryConnection);

struct SerializedMap
{
    SerializedMap()
    {
        Continents = new std::vector<std::string>();
        Countries = new std::vector<std::string>();
        CountryContinentMapping = new std::map<std::string, std::string>();
        CountryConnections = new std::vector<CountryConnection>();
    }

    ~SerializedMap()
    {
        delete Continents;
        delete Countries;
        delete CountryContinentMapping;
        delete CountryConnections;
    }

    std::vector<std::string>* Continents;
    std::vector<std::string>* Countries;
    std::map<std::string, std::string>* CountryContinentMapping;
    std::vector<CountryConnection>* CountryConnections;

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
