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

class Map
{

};
