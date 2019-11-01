#include <iostream>

#include "Map/MapLoader.h"

void runTests();
void generateMaps();

int main(int argc, char** argv)
{

    if (argc == 1)
    {
        runTests();
    }
    else if (argc == 2)
    {
        generateMaps();
    }
    else
    {
        std::cout << "invalid arguments!" << std::endl;
        return -1;
    }


    return 0;
}

void runTests()
{

    // Test 1, Loads valid map, PASS
    {
        MapLoader ml;
        Map* m = ml.loadMap("data/map1.map");
        std::cout << "Test 1: Check that loader can load a map, should PASS, is: " << (m != nullptr ? "PASS" : "FAIL") << std::endl;
    }

    // Test 2, Refuses to load invalid map, corrupted xml, FAIL
    {
        MapLoader ml;
        Map* m = ml.loadMap("data/map_invalid1.map");
        std::cout << "Test 2: Check that loader can load a corrupted map, should FAIL, is: " << (m != nullptr ? "PASS" : "FAIL") << std::endl;
    }

    // Test 3, Refuses to load invalid map, invalid graph structure, FAIL
    {
        MapLoader ml;
        Map* m = ml.loadMap("data/map_invalid2.map");
        std::cout << "Test 2: Check that loader can load a badly structured map, should FAIL, is: " << (m != nullptr ? "PASS" : "FAIL") << std::endl;
    }
}



void generateMaps()
{
    // Map 1
    MapLoader ml;

    {
        SerializedMap sm;

        sm.Continents->emplace_back("C1");
        sm.Continents->emplace_back("C2");
        sm.Continents->emplace_back("C3");
        sm.Continents->emplace_back("C4");
        sm.Continents->emplace_back("C5");

        sm.Countries->emplace_back("1");
        sm.Countries->emplace_back("2");
        sm.Countries->emplace_back("3");
        sm.Countries->emplace_back("4");
        sm.Countries->emplace_back("5");
        sm.Countries->emplace_back("6");
        sm.Countries->emplace_back("7");
        sm.Countries->emplace_back("8");
        sm.Countries->emplace_back("9");
        sm.Countries->emplace_back("10");
        sm.Countries->emplace_back("11");
        sm.Countries->emplace_back("12");
        sm.Countries->emplace_back("13");
        sm.Countries->emplace_back("14");
        sm.Countries->emplace_back("15");
        sm.Countries->emplace_back("16");
        sm.Countries->emplace_back("17");
        sm.Countries->emplace_back("18");
        sm.Countries->emplace_back("19");
        sm.Countries->emplace_back("20");
        sm.Countries->emplace_back("21");
        sm.Countries->emplace_back("22");
        sm.Countries->emplace_back("23");

        sm.CountryContinentMapping->emplace("1", "C1");
        sm.CountryContinentMapping->emplace("2", "C1");
        sm.CountryContinentMapping->emplace("3", "C2");
        sm.CountryContinentMapping->emplace("4", "C2");
        sm.CountryContinentMapping->emplace("5", "C3");
        sm.CountryContinentMapping->emplace("6", "C3");
        sm.CountryContinentMapping->emplace("7", "C3");
        sm.CountryContinentMapping->emplace("8", "C4");
        sm.CountryContinentMapping->emplace("9", "C4");
        sm.CountryContinentMapping->emplace("10", "C4");
        sm.CountryContinentMapping->emplace("11", "C4");
        sm.CountryContinentMapping->emplace("12", "C4");
        sm.CountryContinentMapping->emplace("13", "C4");
        sm.CountryContinentMapping->emplace("14", "C4");
        sm.CountryContinentMapping->emplace("15", "C5");
        sm.CountryContinentMapping->emplace("16", "C5");
        sm.CountryContinentMapping->emplace("17", "C5");
        sm.CountryContinentMapping->emplace("18", "C5");
        sm.CountryContinentMapping->emplace("19", "C5");
        sm.CountryContinentMapping->emplace("20", "C5");
        sm.CountryContinentMapping->emplace("21", "C5");
        sm.CountryContinentMapping->emplace("22", "C5");
        sm.CountryContinentMapping->emplace("23", "C5");

        sm.CountryConnections->emplace_back("1", "2", false);
        sm.CountryConnections->emplace_back("3", "4", false);
        sm.CountryConnections->emplace_back("5", "6", false);
        sm.CountryConnections->emplace_back("6", "7", false);
        sm.CountryConnections->emplace_back("8", "9", false);
        sm.CountryConnections->emplace_back("8", "10", false);
        sm.CountryConnections->emplace_back("8", "11", false);
        sm.CountryConnections->emplace_back("9", "11", false);
        sm.CountryConnections->emplace_back("10", "11", false);
        sm.CountryConnections->emplace_back("10", "12", false);
        sm.CountryConnections->emplace_back("10", "13", false);
        sm.CountryConnections->emplace_back("11", "13", false);
        sm.CountryConnections->emplace_back("11", "14", false);
        sm.CountryConnections->emplace_back("12", "13", false);
        sm.CountryConnections->emplace_back("13", "14", false);
        sm.CountryConnections->emplace_back("15", "16", false);
        sm.CountryConnections->emplace_back("16", "17", false);
        sm.CountryConnections->emplace_back("16", "19", false);
        sm.CountryConnections->emplace_back("16", "20", false);
        sm.CountryConnections->emplace_back("17", "18", false);
        sm.CountryConnections->emplace_back("17", "20", false);
        sm.CountryConnections->emplace_back("17", "23", false);
        sm.CountryConnections->emplace_back("19", "20", false);
        sm.CountryConnections->emplace_back("19", "21", false);
        sm.CountryConnections->emplace_back("20", "21", false);
        sm.CountryConnections->emplace_back("20", "22", false);
        sm.CountryConnections->emplace_back("20", "23", false);
        sm.CountryConnections->emplace_back("21", "22", false);
        sm.CountryConnections->emplace_back("22", "23", false);

        // Water connections
        sm.CountryConnections->emplace_back("1", "8", true);
        sm.CountryConnections->emplace_back("2", "3", true);
        sm.CountryConnections->emplace_back("4", "5", true);
        sm.CountryConnections->emplace_back("4", "15", true);
        sm.CountryConnections->emplace_back("7", "18", true);
        sm.CountryConnections->emplace_back("9", "15", true);
        sm.CountryConnections->emplace_back("14", "19", true);

        ml.saveMap("map1.map", sm);
    }

    // Map 2
    {
        SerializedMap sm;

        sm.Continents->emplace_back("C1");
        sm.Continents->emplace_back("C2");
        sm.Continents->emplace_back("C3");
        sm.Continents->emplace_back("C4");

        sm.Countries->emplace_back("1");
        sm.Countries->emplace_back("2");
        sm.Countries->emplace_back("3");
        sm.Countries->emplace_back("4");
        sm.Countries->emplace_back("5");
        sm.Countries->emplace_back("6");
        sm.Countries->emplace_back("7");
        sm.Countries->emplace_back("8");
        sm.Countries->emplace_back("9");
        sm.Countries->emplace_back("10");
        sm.Countries->emplace_back("11");
        sm.Countries->emplace_back("12");
        sm.Countries->emplace_back("13");
        sm.Countries->emplace_back("14");
        sm.Countries->emplace_back("15");
        sm.Countries->emplace_back("16");
        sm.Countries->emplace_back("17");
        sm.Countries->emplace_back("18");
        sm.Countries->emplace_back("19");
        sm.Countries->emplace_back("20");
        sm.Countries->emplace_back("21");
        sm.Countries->emplace_back("22");
        sm.Countries->emplace_back("23");
        sm.Countries->emplace_back("24");
        sm.Countries->emplace_back("25");

        sm.CountryContinentMapping->emplace("1", "C1");
        sm.CountryContinentMapping->emplace("2", "C1");
        sm.CountryContinentMapping->emplace("3", "C1");
        sm.CountryContinentMapping->emplace("4", "C1");
        sm.CountryContinentMapping->emplace("5", "C1");
        sm.CountryContinentMapping->emplace("6", "C1");
        sm.CountryContinentMapping->emplace("7", "C1");
        sm.CountryContinentMapping->emplace("8", "C2");
        sm.CountryContinentMapping->emplace("9", "C2");
        sm.CountryContinentMapping->emplace("10", "C3");
        sm.CountryContinentMapping->emplace("11", "C3");
        sm.CountryContinentMapping->emplace("12", "C3");
        sm.CountryContinentMapping->emplace("13", "C3");
        sm.CountryContinentMapping->emplace("14", "C3");
        sm.CountryContinentMapping->emplace("15", "C3");
        sm.CountryContinentMapping->emplace("16", "C3");
        sm.CountryContinentMapping->emplace("17", "C3");
        sm.CountryContinentMapping->emplace("18", "C3");
        sm.CountryContinentMapping->emplace("19", "C3");
        sm.CountryContinentMapping->emplace("20", "C3");
        sm.CountryContinentMapping->emplace("21", "C3");
        sm.CountryContinentMapping->emplace("22", "C3");
        sm.CountryContinentMapping->emplace("23", "C4");
        sm.CountryContinentMapping->emplace("24", "C4");
        sm.CountryContinentMapping->emplace("25", "C4");

        sm.CountryConnections->emplace_back("1", "2", false);
        sm.CountryConnections->emplace_back("1", "3", false);
        sm.CountryConnections->emplace_back("1", "4", false);
        sm.CountryConnections->emplace_back("2", "4", false);
        sm.CountryConnections->emplace_back("3", "4", false);
        sm.CountryConnections->emplace_back("3", "5", false);
        sm.CountryConnections->emplace_back("3", "6", false);
        sm.CountryConnections->emplace_back("4", "6", false);
        sm.CountryConnections->emplace_back("5", "7", false);
        sm.CountryConnections->emplace_back("8", "9", false);
        sm.CountryConnections->emplace_back("10", "11", false);
        sm.CountryConnections->emplace_back("11", "13", false);
        sm.CountryConnections->emplace_back("11", "14", false);
        sm.CountryConnections->emplace_back("12", "13", false);
        sm.CountryConnections->emplace_back("12", "19", false);
        sm.CountryConnections->emplace_back("13", "14", false);
        sm.CountryConnections->emplace_back("13", "15", false);
        sm.CountryConnections->emplace_back("13", "19", false);
        sm.CountryConnections->emplace_back("13", "20", false);
        sm.CountryConnections->emplace_back("14", "15", false);
        sm.CountryConnections->emplace_back("15", "16", false);
        sm.CountryConnections->emplace_back("15", "20", false);
        sm.CountryConnections->emplace_back("16", "17", false);
        sm.CountryConnections->emplace_back("17", "18", false);
        sm.CountryConnections->emplace_back("19", "20", false);
        sm.CountryConnections->emplace_back("19", "21", false);
        sm.CountryConnections->emplace_back("20", "21", false);
        sm.CountryConnections->emplace_back("20", "22", false);
        sm.CountryConnections->emplace_back("23", "24", false);
        sm.CountryConnections->emplace_back("24", "25", false);

        // Water Connections
        sm.CountryConnections->emplace_back("2", "10", true);
        sm.CountryConnections->emplace_back("6", "12", true);
        sm.CountryConnections->emplace_back("7", "8", true);
        sm.CountryConnections->emplace_back("9", "19", true);
        sm.CountryConnections->emplace_back("10", "18", true);
        sm.CountryConnections->emplace_back("16", "25", true);
        sm.CountryConnections->emplace_back("21", "23", true);

        ml.saveMap("map2.map", sm);
    }
}