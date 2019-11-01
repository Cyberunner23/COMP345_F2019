#include "MapLoader.h"

Map* MapLoader::loadMap(std::string const& filePath)
{
    std::ifstream f(filePath);

    if (f.fail())
    {
        return nullptr;
    }

    SerializedMap serializedMap;

    try
    {
        f >> serializedMap;
    } catch (std::exception& e)
    {
        return nullptr;
    }


    Map* map = new Map();

    std::map<std::string, SGraph*> continents;
    for (std::string& continent : *serializedMap.Continents)
    {
        continents.emplace(continent, &map->createContinent());
    }

    std::map<std::string, Vertex> countries;
    for (std::string& country : *serializedMap.Countries)
    {
        CountryNode c((unsigned int)std::stoi(country));
        countries.emplace(country, map->addCountry(c));
    }

    for (auto& mapping : *serializedMap.CountryContinentMapping)
    {
        Vertex country = countries[mapping.first];
        SGraph* continent = continents[mapping.second];
        map->addCountry(country, *continent);
    }

    for (auto& connection : *serializedMap.CountryConnections)
    {
        Vertex c1 = countries[*connection.C1];
        Vertex c2 = countries[*connection.C2];
        map->connectRegion(c1, c2, *connection.IsWaterConnection);
    }

    if (map->validate())
    {
        return nullptr;
    }

    return map;
}

void MapLoader::saveMap(std::string const &filePath, SerializedMap &map)
{
    std::ofstream f(filePath, std::fstream::trunc);
    f << map;
}
