#include "MapLoader.h"

bool MapLoader::loadMap(std::string const& filePath)
{
    std::ifstream f(filePath);

    if (f.fail())
    {
        return false;
    }

    SerializedMap serializedMap;

    try
    {
        f >> serializedMap;
    } catch (std::exception& e)
    {
        return false;
    }

    Map::GetInstance().setStartingCountryID(*serializedMap.StartingCountryID);

    std::map<std::string, SGraph*> continents;
    for (std::string& continent : *serializedMap.Continents)
    {
        continents.emplace(continent, &Map::GetInstance().createContinent());
    }

    std::map<std::string, Vertex> countries;
    for (std::string& country : *serializedMap.Countries)
    {
        CountryNode c((unsigned int)std::stoi(country));
        countries.emplace(country, Map::GetInstance().addCountry(c));
    }

    for (auto& mapping : *serializedMap.CountryContinentMapping)
    {
        Vertex country = countries[mapping.first];
        SGraph* continent = continents[mapping.second];
        Map::GetInstance().addCountry(country, *continent);
    }

    for (auto& connection : *serializedMap.CountryConnections)
    {
        Vertex c1 = countries[*connection.C1];
        Vertex c2 = countries[*connection.C2];
        Map::GetInstance().connectRegion(c1, c2, *connection.IsWaterConnection);
    }

    if (Map::GetInstance().validate())
    {
        return false;
    }

    return true;
}

void MapLoader::saveMap(std::string const &filePath, SerializedMap &map)
{
    std::ofstream f(filePath, std::fstream::trunc);
    f << map;
}
