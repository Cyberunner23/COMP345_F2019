#include "Map.h"

CountryNode::CountryNode()
{
    OwnedBy = new std::string();
    Armies = new std::vector<std::string>();
}

SGraph& Map::createContinent()
{
    return _mainGraph->create_subgraph();
}

std::pair<ContinentIterator, ContinentIterator> Map::getContinentIterators()
{
    return _mainGraph->children();
}

Vertex Map::addCountry(const CountryNode& region)
{
    Vertex v = boost::add_vertex(*_mainGraph);
    VertexDataPropertyMap dataMap = boost::get(vertex_data, *_mainGraph);
    dataMap[v] = region;

    return v;
}

Vertex Map::addCountry(const Vertex& regionVertex, SGraph& subGraph)
{
    return boost::add_vertex(regionVertex, subGraph);
}

Edge Map::connectRegion(const Vertex& v1, const Vertex& v2)
{
    return connectRegion(v1, v2, *_mainGraph);
}

Edge Map::connectRegion(const Vertex& v1, const Vertex& v2, SGraph& subGraph)
{
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

