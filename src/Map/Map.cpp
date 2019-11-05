#include <Deck/Deck.h>
#include "Map.h"

CountryNode::CountryNode(unsigned int countryID)
{
    CountryID = new unsigned int(countryID);
    CitiesInCountry = new std::vector<Cities>();
    ArmiesInCountry = new std::vector<Armies>();
}

bool CountryNode::canDestroyArmy(Armies playerArmyColor)
{
    return ArmiesInCountry->empty() || (ArmiesInCountry->size() == 1 && ArmiesInCountry->at(0) == playerArmyColor);
}

void CountryNode::destroyArmy(Armies armyToDestroy)
{
    auto it = std::find(ArmiesInCountry->begin(), ArmiesInCountry->end(), armyToDestroy);
    ArmiesInCountry->erase(it);
}

std::optional<Armies> CountryNode::getCountryOwner()
{
    std::map<Armies, unsigned int> map;

    Armies maxColor = Armies::YELLOW;
    unsigned int maxCount = 0;

    if (ArmiesInCountry->empty())
    {
        return std::nullopt;
    }

    for (auto color : *ArmiesInCountry)
    {
        map[color]++;
    }

    for (auto pair : map)
    {
        if (pair.second > maxCount)
        {
            maxCount = pair.second;
            maxColor = pair.first;
        }
    }

    unsigned int numFoundMax = 0;
    for (auto pair : map)
    {
        if (pair.second == maxCount)
        {
            numFoundMax++;
        }
    }

    if (numFoundMax > 1)
    {
        return std::nullopt;
    }

    if (maxCount != 0)
    {
        return maxColor;
    }

    return std::nullopt;
}

void Map::dump()
{
    auto iterators = getVertexIterators();
    VertexDataPropertyMap map = boost::get(vertex_data, *_mainGraph);
    Deck d;

    for (auto it = iterators.first; it != iterators.second; ++it)
    {
        CountryNode* node = &map[*it];
        std::cout << "----------------------------------------" << std::endl;
        std::cout << "Country ID: " << *node->CountryID << std::endl;
        std::cout << "Cities in country:" << std::endl;
        for (auto city : *node->CitiesInCountry)
        {
            std::cout << d.CitiesMap->at(city) << std::endl;
        }
        std::cout << "Armies in country:" << std::endl;
        for (auto army : *node->ArmiesInCountry)
        {
            std::cout << d.ArmiesMap->at(army) << std::endl;
        }

        std::cout << "Countries connected to this one:" << std::endl;
        auto adjacent_vertices = boost::adjacent_vertices(*it, *_mainGraph);
        for (auto it2 = adjacent_vertices.first; it2 != adjacent_vertices.second; ++it2)
        {
            CountryNode* adjacentNode = &map[*it2];
            std::cout << *adjacentNode->CountryID << std::endl;
        }
    }
}

std::vector<Armies> Map::getContinentOwners()
{
    std::vector<Armies> owners;

    VertexDataPropertyMap dataMap = boost::get(vertex_data, *_mainGraph);

    auto continentIterators = getContinentIterators();
    for (auto it = continentIterators.first; it != continentIterators.second; ++it)
    {
        auto countryIterators = boost::vertices(*it);
        std::vector<CountryNode*> countries;
        for (auto it2 = countryIterators.first; it2 != countryIterators.second; ++it2)
        {
            countries.push_back(&dataMap[*it2]);
        }

        std::map<Armies, unsigned int> ownerMapping;

        Armies maxColor = Armies::YELLOW;
        unsigned int maxCount = 0;

        for (auto color : countries)
        {
            auto owner = color->getCountryOwner();
            if (owner)
            {
                ownerMapping[*owner]++;
            }
        }

        for (auto pair : ownerMapping)
        {
            if (pair.second > maxCount)
            {
                maxCount = pair.second;
                maxColor = pair.first;
            }
        }

        unsigned int numFoundMax = 0;
        for (auto pair : ownerMapping)
        {
            if (pair.second == maxCount)
            {
                numFoundMax++;
            }
        }

        if (numFoundMax > 1)
        {
            continue;
        }

        if (maxCount != 0)
        {
            owners.push_back(maxColor);
        }
    }

    return owners;
}

std::vector<Armies> Map::getCountryOwners()
{
    std::vector<Armies> countryOwners;
    VertexDataPropertyMap dataMap = boost::get(vertex_data, *_mainGraph);

    auto vertexIterator = getVertexIterators();

    for (auto it = vertexIterator.first; it != vertexIterator.second; ++it)
    {
        CountryNode* node = &dataMap[*it];
        auto countryOwner = node->getCountryOwner();
        if (countryOwner)
        {
            countryOwners.push_back(*countryOwner);
        }
    }

    return countryOwners;
}

SGraph& Map::createContinent()
{
    return _mainGraph->create_subgraph();
}

std::pair<ContinentIterator, ContinentIterator> Map::getContinentIterators()
{
    return _mainGraph->children();
}

std::pair<VertexIterator, VertexIterator> Map::getVertexIterators()
{
    return boost::vertices(*_mainGraph);
}

unsigned int Map::getNumCountries()
{
    return boost::num_vertices(*_mainGraph);
}



Vertex Map::addCountry(const CountryNode& region)
{
    Vertex v = boost::add_vertex(*_mainGraph);
    VertexDataPropertyMap dataMap = boost::get(vertex_data, *_mainGraph);
    dataMap[v] = region;

    return v;
}

CountryNode* Map::getCountryNode(Vertex& regionVertex)
{
    VertexDataPropertyMap dataMap = boost::get(vertex_data, *_mainGraph);
    return &dataMap[regionVertex];
}

void Map::setCountryNode(Vertex& regionVertex, CountryNode& country)
{
    VertexDataPropertyMap dataMap = boost::get(vertex_data, *_mainGraph);
    dataMap[regionVertex] = country;
}

bool Map::findVertexByCountryID(unsigned int ID, Vertex& v)
{
    auto iterPair = getVertexIterators();
    VertexDataPropertyMap dataMap = boost::get(vertex_data, *_mainGraph);
    for(; iterPair.first != iterPair.second; ++iterPair.first)
    {
        if (*dataMap[*iterPair.first].CountryID == ID)
        {
            v = *iterPair.first;
            return true;
        }
    }

    return false;
}

CountryNode* Map::findCountryByID(unsigned int ID)
{
    Vertex v;
    if (findVertexByCountryID(ID, v))
    {
        VertexDataPropertyMap dataMap = boost::get(vertex_data, *_mainGraph);
        return &dataMap[v];
    }

    return nullptr;
}

bool Map::areCountriesConnectedByWater(unsigned int id1, unsigned int id2)
{

    Vertex v1;
    Vertex v2;

    if (!findVertexByCountryID(id1, v1))
    {
        throw std::runtime_error("Cant find country ID: " + std::to_string(id1));
    }

    if (!findVertexByCountryID(id2, v2))
    {
        throw std::runtime_error("Cant find country ID: " + std::to_string(id2));
    }

    auto result = boost::edge(v1, v2, *_mainGraph);
    if (result.second)
    {
        EdgeDataPropertyMap dataMap = boost::get(edge_data, *_mainGraph);
        return dataMap[result.first]; // Is water connection
    }

    return false;
}

bool Map::areCountriesConnected(unsigned int id1, unsigned int id2)
{
    Vertex v1;
    Vertex v2;

    if (!findVertexByCountryID(id1, v1))
    {
        throw std::runtime_error("Cant find country ID: " + std::to_string(id1));
    }

    if (!findVertexByCountryID(id2, v2))
    {
        throw std::runtime_error("Cant find country ID: " + std::to_string(id2));
    }

    auto result = boost::edge(v1, v2, *_mainGraph);
    return result.second;
}

Vertex Map::addCountry(const Vertex& regionVertex, SGraph& subGraph)
{
    return boost::add_vertex(regionVertex, subGraph);
}

Edge Map::connectRegion(const Vertex& v1, const Vertex& v2)
{
    return connectRegion(v1, v2, false);
}

Edge Map::connectRegion(const Vertex& v1, const Vertex& v2, bool isWaterConnection)
{
    return connectRegion(v1, v2, isWaterConnection, *_mainGraph);
}

Edge Map::connectRegion(const Vertex& v1, const Vertex& v2, SGraph& subGraph)
{
    return connectRegion(v1, v2, false, subGraph);
}

Edge Map::connectRegion(const Vertex& v1, const Vertex& v2, bool isWaterConnection, SGraph& subGraph)
{
    Edge e = boost::add_edge(v1, v2, subGraph).first;
    EdgeDataPropertyMap dataMap = boost::get(edge_data, subGraph);
    dataMap[e] = isWaterConnection;

    return e;
}


unsigned int Map::getStartingCountryID()
{
    return boost::get_property(*_mainGraph, graph_data);
}

void Map::setStartingCountryID(unsigned int ID)
{
    boost::get_property(*_mainGraph, graph_data) = ID;
}

bool Map::isConnected()
{
    return isConnected(*_mainGraph);
}

bool Map::isConnected(SGraph &graph)
{
    std::vector<int> component(boost::num_vertices(graph));
    return boost::connected_components(graph, &component[0]) == 1;
}

int Map::validate()
{
    // Validate Graph is connected
    if (!isConnected())
    {
        return -1;
    }

    // Validate sub-graphs are connected
    auto iterators = getContinentIterators();
    for (auto it = iterators.first; it != iterators.second; it++)
    {
        if (!isConnected(*it))
        {
            return -2;
        }
    }

    // Validate that no country is in more than one continent
    iterators = getContinentIterators();
    if (iterators.first != iterators.second)
    {
        unsigned int totalCountries = boost::num_vertices(*_mainGraph);
        unsigned int runningTotal = 0;

        for (auto it = iterators.first; it != iterators.second; it++)
        {
            runningTotal += boost::num_vertices(*it);
        }

        if (totalCountries != runningTotal)
        {
            return -3;
        }
    }

    return 0;
}

