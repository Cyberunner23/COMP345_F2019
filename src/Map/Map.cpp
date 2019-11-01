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
    unsigned int count = 0;

    auto iterators = getContinentIterators();
    for (auto it = iterators.first; it != iterators.second; it++)
    {
        auto continent = *it;
        auto childIterators = continent.children();
        for (auto it2 = childIterators.first; it2 != childIterators.second; it2++)
        {
            count++;
        }
    }

    return count;
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

CountryNode* Map::findCountryByID(unsigned int ID)
{
    auto iterPair = getVertexIterators();
    VertexDataPropertyMap dataMap = boost::get(vertex_data, *_mainGraph);
    for(; iterPair.first != iterPair.second; ++iterPair.first)
    {
        if (*dataMap[*iterPair.first].CountryID == ID)
        {
            return &dataMap[*iterPair.first];
        }
    }

    return nullptr;
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

    return boost::add_edge(v1, v2, subGraph).first;
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

