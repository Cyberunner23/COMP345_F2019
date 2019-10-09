#include "Map.h"


SGraph& Map::createSubGraph()
{
    return _mainGraph.create_subgraph();
}

SGraph& Map::createSubGraph(SGraph &subGraph)
{
    return subGraph.create_subgraph();
}

Vertex Map::addRegion(const CountryNode& region)
{
    Vertex v = boost::add_vertex(_mainGraph);

    VertexDataPropertyMap dataMap = boost::get(vertex_data, _mainGraph);
    VertexDisplaytxtPropertyMap displayMap = boost::get(vertex_displaytxt, _mainGraph);

    displayMap[v] = region._name;
    dataMap[v] = region;

    return v;
}

Vertex Map::addRegion(const Vertex& regionVertex, SGraph& subGraph)
{
    return boost::add_vertex(regionVertex, subGraph);
}

Edge Map::connectRegion(const Vertex& v1, const Vertex& v2)
{
    return connectRegion(v1, v2, _mainGraph);
}

Edge Map::connectRegion(const Vertex& v1, const Vertex& v2, SGraph& subGraph)
{
    return boost::add_edge(v1, v2, subGraph).first;
}

bool Map::isConnected()
{
    return isConnected(_mainGraph);
}

bool Map::isConnected(SGraph &graph)
{
    std::vector<int> component(boost::num_vertices(graph));
    return boost::connected_components(graph, &component[0]) == 1;
}
