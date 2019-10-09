#pragma once

#include <fstream>
#include <memory>
#include <string>
#include <vector>

#include "boost/graph/adjacency_list.hpp"
#include "boost/graph/connected_components.hpp"
#include "boost/graph/graph_traits.hpp"
#include "boost/graph/graphml.hpp"
#include "boost/graph/graphviz.hpp"
#include "boost/graph/subgraph.hpp"
#include "boost/graph/properties.hpp"

#include "Utils/SerializationUtils.hpp"

//---------------------------------------------------------
// Country Node
//---------------------------------------------------------

struct CountryNode
{

    std::string* OwnedBy; // Player
    std::vector<std::string> Armies;

    SERIALIZE(archive,
    {
        archive & NameValuePair("Player", OwnedBy);
        archive & NameValuePair("Armies", Armies);
    })
};
SERIALIZE_CLEANUP(CountryNode)
SERIALIZE_CLEANUP(std::vector<std::string>)




//---------------------------------------------------------
// Map
//---------------------------------------------------------

// Custom property for node data
enum vertex_data_t
{
    vertex_data
};

// Custom property for the display text of the node.
// Will be used to display text in the cells in the graphviz export
enum vertex_displayTxt_t
{
    vertex_displayTxt
};

// Registering the new properties
namespace boost
{
    BOOST_INSTALL_PROPERTY(vertex, data);
    BOOST_INSTALL_PROPERTY(vertex, displayTxt);
}

// The graph. Uses Boost::graph.
// Created a graph with an adjacency list implementation.
// It includes the custom properties I defined above.
typedef boost::subgraph<
        boost::adjacency_list<
                boost::vecS,
                boost::vecS,
                boost::undirectedS,
                boost::property<boost::vertex_index_t, int,
                boost::property<vertex_data_t, CountryNode,
                boost::property<vertex_displayTxt_t, std::string>>>,
                boost::property<boost::edge_index_t, int>
        >> SGraph;

// Type for the vertices
typedef typename boost::graph_traits<SGraph>::vertex_descriptor Vertex;
// Type for the edges
typedef typename boost::graph_traits<SGraph>::edge_descriptor Edge;

// Type for the vertex iterator, used to go through the list of vertices
typedef typename boost::graph_traits<SGraph>::vertex_iterator VertexIterator;

// Type for the PropertyMap of the vertex data.
// Used to extract the node data.
typedef typename boost::property_map<SGraph, vertex_data_t>::type VertexDataPropertyMap;
// Type for the PropertyMap of the DisplayTxt, used to get/set the data to be displayed in the graphVis output.
typedef typename boost::property_map<SGraph, vertex_displayTxt_t>::type VertexDisplayTxtPropertyMap;

class Map
{

    Map() = default;

    SGraph* getGraph()
    {
        return _mainGraph;
    }

    void setGraph(SGraph* graph)
    {
        _mainGraph = graph;
    }

    // Creates a sub-graph from the main graph.
    SGraph& createSubGraph();

    // Creates a sub-graph from the the provided sub-graph.
    SGraph& createSubGraph(SGraph& subGraph);

    // Adds a RegionNode to the main graph.
    Vertex addRegion(const CountryNode& region);

    // Adds a RegionNode to the provided sub-graph.
    Vertex addRegion(const Vertex& regionVertex, SGraph& subGraph);

    // Creates an edge between the provided region vertices from the main graph.
    // Used when generating maps from code.
    Edge connectRegion(const Vertex& v1, const Vertex& v2);

    // Creates an edge between the provided region vertices from a subgraph.
    // Used when generating maps from code.
    Edge connectRegion(const Vertex& v1, const Vertex& v2, SGraph& subGraph);

    // Verifies whether the main graph is connected or not
    bool isConnected();

    // Verifies whether the provided subgraph is connected or not.
    bool isConnected(SGraph& subGraph);

private:

    SGraph* _mainGraph;
};
