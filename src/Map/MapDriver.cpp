
#include "Map/Map.h"

int main(int argc, char** argv)
{

    // Check if connected graph, VALID
    {
        Map map;
        Vertex a = map.addCountry(CountryNode());
        Vertex b = map.addCountry(CountryNode());
        Vertex c = map.addCountry(CountryNode());
        Vertex d = map.addCountry(CountryNode());

        map.connectRegion(b, c);
        map.connectRegion(c, d);
        map.connectRegion(a, b);

        std::cout << "TEST 1: Check if connected graph passes check, should PASS, is " << (map.validate() == 0 ? "PASS" : "FAIL") << std::endl;
    }

    // Check if connected graph, INVALID
    {
        Map map;
        Vertex a = map.addCountry(CountryNode());
        Vertex b = map.addCountry(CountryNode());
        Vertex c = map.addCountry(CountryNode());
        Vertex d = map.addCountry(CountryNode());

        map.connectRegion(a, b);
        map.connectRegion(b, c);

        std::cout << "TEST 2: Check if non connected graph passes check, should FAIL, is " << (map.validate() == 0 ? "PASS" : "FAIL") << std::endl;
    }

    // Check if connected sub-graph, VALID
    {
        Map map;

        SGraph& continent1 = map.createContinent();
        SGraph& continent2 = map.createContinent();

        Vertex a = map.addCountry(CountryNode());
        Vertex b = map.addCountry(CountryNode());
        Vertex c = map.addCountry(CountryNode());
        Vertex d = map.addCountry(CountryNode());

        map.addCountry(a, continent1);
        map.addCountry(b, continent1);
        map.addCountry(c, continent2);
        map.addCountry(d, continent2);

        map.connectRegion(a, b);
        map.connectRegion(b, c);
        map.connectRegion(c, d);

        std::cout << "TEST 3: Check if connected sub-graphs passes check, should PASS, is " << (map.validate() == 0 ? "PASS" : "FAIL") << std::endl;
    }

    // Check if connected sub-graph, INVALID
    {
        Map map;

        SGraph& continent1 = map.createContinent();
        SGraph& continent2 = map.createContinent();

        Vertex a = map.addCountry(CountryNode());
        Vertex b = map.addCountry(CountryNode());
        Vertex c = map.addCountry(CountryNode());
        Vertex d = map.addCountry(CountryNode());

        map.addCountry(a, continent1);
        map.addCountry(b, continent1);
        map.addCountry(c, continent2);
        map.addCountry(d, continent2);

        map.connectRegion(b, c);
        map.connectRegion(c, d);

        std::cout << "TEST 4: Check if non connected sub-graphs passes check, should FAIL, is " << (map.validate() == 0 ? "PASS" : "FAIL") << std::endl;


    }

    // Check if not a single country is in multiple continents, VALID
    {
        Map map;

        SGraph& continent1 = map.createContinent();
        SGraph& continent2 = map.createContinent();

        Vertex a = map.addCountry(CountryNode());
        Vertex b = map.addCountry(CountryNode());
        Vertex c = map.addCountry(CountryNode());
        Vertex d = map.addCountry(CountryNode());

        map.addCountry(a, continent1);
        map.addCountry(b, continent1);
        map.addCountry(c, continent2);
        map.addCountry(d, continent2);

        map.connectRegion(a, b);
        map.connectRegion(b, c);
        map.connectRegion(c, d);

        std::cout << "TEST 5: Check if no country in 2 continents passes check, should PASS, is " << (map.validate() == 0 ? "PASS" : "FAIL") << std::endl;
    }

    // Check if not a single country is in multiple continents, INVALID
    {
        Map map;

        SGraph& continent1 = map.createContinent();
        SGraph& continent2 = map.createContinent();

        Vertex a = map.addCountry(CountryNode());
        Vertex b = map.addCountry(CountryNode());
        Vertex c = map.addCountry(CountryNode());
        Vertex d = map.addCountry(CountryNode());

        map.addCountry(a, continent1);
        map.addCountry(b, continent1);
        map.addCountry(a, continent2);
        map.addCountry(c, continent2);
        map.addCountry(d, continent2);

        map.connectRegion(a, b);
        map.connectRegion(b, c);
        map.connectRegion(c, d);

        std::cout << "TEST 2: Check if a country in 2 continents passes check, should FAIL, is " << (map.validate() == 0 ? "PASS" : "FAIL") << std::endl;
    }

    return 0;
}
