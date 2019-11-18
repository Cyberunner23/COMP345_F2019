
#include "Map/Map.h"

int main(int argc, char** argv)
{

    // Check if connected graph, VALID
    {
        Vertex a = Map::GetInstance().addCountry(CountryNode());
        Vertex b = Map::GetInstance().addCountry(CountryNode());
        Vertex c = Map::GetInstance().addCountry(CountryNode());
        Vertex d = Map::GetInstance().addCountry(CountryNode());

        Map::GetInstance().connectRegion(b, c);
        Map::GetInstance().connectRegion(c, d);
        Map::GetInstance().connectRegion(a, b);

        std::cout << "TEST 1: Check if connected graph passes check, should PASS, is " << (Map::GetInstance().validate() == 0 ? "PASS" : "FAIL") << std::endl;
    }

    // Check if connected graph, INVALID
    {
        Vertex a = Map::GetInstance().addCountry(CountryNode());
        Vertex b = Map::GetInstance().addCountry(CountryNode());
        Vertex c = Map::GetInstance().addCountry(CountryNode());
        Vertex d = Map::GetInstance().addCountry(CountryNode());

        Map::GetInstance().connectRegion(a, b);
        Map::GetInstance().connectRegion(b, c);

        std::cout << "TEST 2: Check if non connected graph passes check, should FAIL, is " << (Map::GetInstance().validate() == 0 ? "PASS" : "FAIL") << std::endl;
    }

    // Check if connected sub-graph, VALID
    {
        SGraph& continent1 = Map::GetInstance().createContinent();
        SGraph& continent2 = Map::GetInstance().createContinent();

        Vertex a = Map::GetInstance().addCountry(CountryNode());
        Vertex b = Map::GetInstance().addCountry(CountryNode());
        Vertex c = Map::GetInstance().addCountry(CountryNode());
        Vertex d = Map::GetInstance().addCountry(CountryNode());

        Map::GetInstance().addCountry(a, continent1);
        Map::GetInstance().addCountry(b, continent1);
        Map::GetInstance().addCountry(c, continent2);
        Map::GetInstance().addCountry(d, continent2);

        Map::GetInstance().connectRegion(a, b);
        Map::GetInstance().connectRegion(b, c);
        Map::GetInstance().connectRegion(c, d);

        std::cout << "TEST 3: Check if connected sub-graphs passes check, should PASS, is " << (Map::GetInstance().validate() == 0 ? "PASS" : "FAIL") << std::endl;
    }

    // Check if connected sub-graph, INVALID
    {
        SGraph& continent1 = Map::GetInstance().createContinent();
        SGraph& continent2 = Map::GetInstance().createContinent();

        Vertex a = Map::GetInstance().addCountry(CountryNode());
        Vertex b = Map::GetInstance().addCountry(CountryNode());
        Vertex c = Map::GetInstance().addCountry(CountryNode());
        Vertex d = Map::GetInstance().addCountry(CountryNode());

        Map::GetInstance().addCountry(a, continent1);
        Map::GetInstance().addCountry(b, continent1);
        Map::GetInstance().addCountry(c, continent2);
        Map::GetInstance().addCountry(d, continent2);

        Map::GetInstance().connectRegion(b, c);
        Map::GetInstance().connectRegion(c, d);

        std::cout << "TEST 4: Check if non connected sub-graphs passes check, should FAIL, is " << (Map::GetInstance().validate() == 0 ? "PASS" : "FAIL") << std::endl;


    }

    // Check if not a single country is in multiple continents, VALID
    {
        SGraph& continent1 = Map::GetInstance().createContinent();
        SGraph& continent2 = Map::GetInstance().createContinent();

        Vertex a = Map::GetInstance().addCountry(CountryNode());
        Vertex b = Map::GetInstance().addCountry(CountryNode());
        Vertex c = Map::GetInstance().addCountry(CountryNode());
        Vertex d = Map::GetInstance().addCountry(CountryNode());

        Map::GetInstance().addCountry(a, continent1);
        Map::GetInstance().addCountry(b, continent1);
        Map::GetInstance().addCountry(c, continent2);
        Map::GetInstance().addCountry(d, continent2);

        Map::GetInstance().connectRegion(a, b);
        Map::GetInstance().connectRegion(b, c);
        Map::GetInstance().connectRegion(c, d);

        std::cout << "TEST 5: Check if no country in 2 continents passes check, should PASS, is " << (Map::GetInstance().validate() == 0 ? "PASS" : "FAIL") << std::endl;
    }

    // Check if not a single country is in multiple continents, INVALID
    {
        SGraph& continent1 = Map::GetInstance().createContinent();
        SGraph& continent2 = Map::GetInstance().createContinent();

        Vertex a = Map::GetInstance().addCountry(CountryNode());
        Vertex b = Map::GetInstance().addCountry(CountryNode());
        Vertex c = Map::GetInstance().addCountry(CountryNode());
        Vertex d = Map::GetInstance().addCountry(CountryNode());

        Map::GetInstance().addCountry(a, continent1);
        Map::GetInstance().addCountry(b, continent1);
        Map::GetInstance().addCountry(a, continent2);
        Map::GetInstance().addCountry(c, continent2);
        Map::GetInstance().addCountry(d, continent2);

        Map::GetInstance().connectRegion(a, b);
        Map::GetInstance().connectRegion(b, c);
        Map::GetInstance().connectRegion(c, d);

        std::cout << "TEST 6: Check if a country in 2 continents passes check, should FAIL, is " << (Map::GetInstance().validate() == 0 ? "PASS" : "FAIL") << std::endl;
    }

    return 0;
}
