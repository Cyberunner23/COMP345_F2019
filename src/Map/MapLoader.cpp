#include "MapLoader.h"

Map* MapLoader::loadMap(std::string const& filePath)
{
    std::ifstream f(filePath);

    if (f.fail())
    {
        return nullptr;
    }

    SerializedMap serializedMap;
    f >> serializedMap;

    Map* map = new Map();

    std::map<std::string, SGraph*> continents;
    for (std::string& continent : *serializedMap.Continents)
    {
        continents.emplace(continent, &map->createContinent());
    }

    std::map<std::string, Vertex> countries;
    for (std::string& country : *serializedMap.Countries)
    {
        CountryNode c;
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
        Vertex c1 = countries[connection.first];
        Vertex c2 = countries[connection.second];
        map->connectRegion(c1, c2);
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
