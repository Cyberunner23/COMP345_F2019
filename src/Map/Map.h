#pragma once
#define BOOST_ALL_NO_LIB

#include <fstream>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "boost/graph/adjacency_list.hpp"
#include "boost/graph/connected_components.hpp"
#include "boost/graph/graph_traits.hpp"
#include "boost/graph/graphml.hpp"
#include "boost/graph/graphviz.hpp"
#include "boost/graph/subgraph.hpp"
#include "boost/graph/properties.hpp"

#include "Deck/Deck.h"
#include "Utils/SerializationUtils.hpp"

//---------------------------------------------------------
// Country Node
//---------------------------------------------------------

struct CountryNode
{
    explicit CountryNode(unsigned int countryID);
    CountryNode() : CountryNode(0) {}

    bool canDestroyArmy(Armies playerArmyColor);
    void destroyArmy(Armies armyToDestroy);

    unsigned int* CountryID;

    std::optional<Armies> getCountryOwner();

    std::vector<Cities>* CitiesInCountry;
    std::vector<Armies>* ArmiesInCountry;
};


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

enum edge_data_t
{
    edge_data
};

enum graph_data_t
{
    graph_data
};

// Registering the new properties
namespace boost
{
    BOOST_INSTALL_PROPERTY(vertex, data);
    BOOST_INSTALL_PROPERTY(vertex, displayTxt);
    BOOST_INSTALL_PROPERTY(edge, data);
    BOOST_INSTALL_PROPERTY(graph, data);
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

                boost::property<boost::edge_index_t, int,
                        boost::property<edge_data_t, bool>>,

                boost::property<graph_data_t, unsigned int>
        >> SGraph;

// Type for the vertices
typedef typename boost::graph_traits<SGraph>::vertex_descriptor Vertex;
// Type for the edges
typedef typename boost::graph_traits<SGraph>::edge_descriptor Edge;

// Type for the vertex iterator, used to go through the list of vertices
typedef typename boost::graph_traits<SGraph>::vertex_iterator VertexIterator;
typedef typename SGraph::children_iterator ContinentIterator;

// Type for the PropertyMap of the vertex data.
// Used to extract the node data.
typedef typename boost::property_map<SGraph, vertex_data_t>::type VertexDataPropertyMap;
// Type for the PropertyMap of the DisplayTxt, used to get/set the data to be displayed in the graphVis output.
typedef typename boost::property_map<SGraph, vertex_displayTxt_t>::type VertexDisplayTxtPropertyMap;

typedef typename boost::property_map<SGraph, edge_data_t>::type EdgeDataPropertyMap;

class Map
{

public:
    Map()
    {
        _mainGraph = new SGraph;
    }

    SGraph* getGraph()
    {
        return _mainGraph;
    }

    /*void exportMapGraphViz(std::string fileName)
    {
        std::ofstream out(fileName);
        boost::dynamic_properties dp;
        dp.property("node_id", boost::get(boost::vertex_index, *_mainGraph));
        dp.property("label", boost::get(boost::vertex_index, *_mainGraph));

        boost::write_graphviz_dp(out, *_mainGraph, dp);
    }*/

    void dump();

    // Creates a sub-graph from the main graph.
    SGraph& createContinent();

    std::pair<ContinentIterator, ContinentIterator> getContinentIterators();
    std::pair<VertexIterator, VertexIterator> getVertexIterators();
    unsigned int getNumCountries();

    unsigned int getStartingCountryID();
    void setStartingCountryID(unsigned int ID);

    // Adds a RegionNode to the main graph.
    Vertex addCountry(const CountryNode& region);

    // Adds a RegionNode to the provided sub-graph.
    Vertex addCountry(const Vertex& regionVertex, SGraph& subGraph);

    CountryNode* getCountryNode(Vertex& regionVertex);
    void setCountryNode(Vertex& regionVertex, CountryNode& country);

    bool findVertexByCountryID(unsigned int ID, Vertex& v);
    CountryNode* findCountryByID(unsigned int ID);
    bool areCountriesConnectedByWater(unsigned int id1, unsigned int id2);
    bool areCountriesConnected(unsigned int id1, unsigned int id2);

    // Creates an edge between the provided region vertices from the main graph.
    // Used when generating maps from code.
    Edge connectRegion(const Vertex& v1, const Vertex& v2);
    Edge connectRegion(const Vertex& v1, const Vertex& v2, bool isWaterConnection);

    // Creates an edge between the provided region vertices from a subgraph.
    // Used when generating maps from code.
    Edge connectRegion(const Vertex& v1, const Vertex& v2, SGraph& subGraph);
    Edge connectRegion(const Vertex& v1, const Vertex& v2, bool isWaterConnection, SGraph& subGraph);

    // Verifies whether the main graph is connected or not
    bool isConnected();

    // Verifies whether the provided subgraph is connected or not.
    bool isConnected(SGraph& subGraph);

    int validate();

private:

    SGraph* _mainGraph;
};