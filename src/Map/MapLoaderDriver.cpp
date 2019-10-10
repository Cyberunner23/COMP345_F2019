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

    MapLoader ml;

    if (!ml.loadMap("map1.map"))
    {
        std::cout << "error!" << std::endl;
    }
    else
    {
        std::cout << "success!" << std::endl;
    }

    if (!ml.loadMap("map2.map"))
    {
        std::cout << "error!" << std::endl;
    }
    else
    {
        std::cout << "success!" << std::endl;
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

        sm.CountryConnections->emplace_back("1", "2");
        sm.CountryConnections->emplace_back("3", "4");
        sm.CountryConnections->emplace_back("5", "6");
        sm.CountryConnections->emplace_back("6", "7");
        sm.CountryConnections->emplace_back("8", "9");
        sm.CountryConnections->emplace_back("8", "10");
        sm.CountryConnections->emplace_back("8", "11");
        sm.CountryConnections->emplace_back("9", "11");
        sm.CountryConnections->emplace_back("10", "11");
        sm.CountryConnections->emplace_back("10", "12");
        sm.CountryConnections->emplace_back("10", "13");
        sm.CountryConnections->emplace_back("11", "13");
        sm.CountryConnections->emplace_back("11", "14");
        sm.CountryConnections->emplace_back("12", "13");
        sm.CountryConnections->emplace_back("13", "14");
        sm.CountryConnections->emplace_back("15", "16");
        sm.CountryConnections->emplace_back("16", "17");
        sm.CountryConnections->emplace_back("16", "19");
        sm.CountryConnections->emplace_back("16", "20");
        sm.CountryConnections->emplace_back("17", "18");
        sm.CountryConnections->emplace_back("17", "20");
        sm.CountryConnections->emplace_back("17", "23");
        sm.CountryConnections->emplace_back("19", "20");
        sm.CountryConnections->emplace_back("19", "21");
        sm.CountryConnections->emplace_back("20", "21");
        sm.CountryConnections->emplace_back("20", "22");
        sm.CountryConnections->emplace_back("20", "23");
        sm.CountryConnections->emplace_back("21", "22");
        sm.CountryConnections->emplace_back("22", "23");

        sm.CountryConnections->emplace_back("1", "8");
        sm.CountryConnections->emplace_back("2", "3");
        sm.CountryConnections->emplace_back("4", "5");
        sm.CountryConnections->emplace_back("4", "15");
        sm.CountryConnections->emplace_back("7", "18");
        sm.CountryConnections->emplace_back("9", "15");
        sm.CountryConnections->emplace_back("14", "19");

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

        sm.CountryConnections->emplace_back("1", "2");
        sm.CountryConnections->emplace_back("1", "3");
        sm.CountryConnections->emplace_back("1", "4");
        sm.CountryConnections->emplace_back("2", "4");
        sm.CountryConnections->emplace_back("3", "4");
        sm.CountryConnections->emplace_back("3", "5");
        sm.CountryConnections->emplace_back("3", "6");
        sm.CountryConnections->emplace_back("4", "6");
        sm.CountryConnections->emplace_back("5", "7");
        sm.CountryConnections->emplace_back("8", "9");
        sm.CountryConnections->emplace_back("10", "11");
        sm.CountryConnections->emplace_back("11", "13");
        sm.CountryConnections->emplace_back("11", "14");
        sm.CountryConnections->emplace_back("12", "13");
        sm.CountryConnections->emplace_back("12", "19");
        sm.CountryConnections->emplace_back("13", "14");
        sm.CountryConnections->emplace_back("13", "15");
        sm.CountryConnections->emplace_back("13", "19");
        sm.CountryConnections->emplace_back("13", "20");
        sm.CountryConnections->emplace_back("14", "15");
        sm.CountryConnections->emplace_back("15", "16");
        sm.CountryConnections->emplace_back("15", "20");
        sm.CountryConnections->emplace_back("16", "17");
        sm.CountryConnections->emplace_back("17", "18");
        sm.CountryConnections->emplace_back("19", "20");
        sm.CountryConnections->emplace_back("19", "21");
        sm.CountryConnections->emplace_back("20", "21");
        sm.CountryConnections->emplace_back("20", "22");
        sm.CountryConnections->emplace_back("23", "24");
        sm.CountryConnections->emplace_back("24", "25");

        sm.CountryConnections->emplace_back("2", "10");
        sm.CountryConnections->emplace_back("6", "12");
        sm.CountryConnections->emplace_back("7", "8");
        sm.CountryConnections->emplace_back("9", "19");
        sm.CountryConnections->emplace_back("10", "18");
        sm.CountryConnections->emplace_back("16", "25");
        sm.CountryConnections->emplace_back("21", "23");

        ml.saveMap("map2.map", sm);
    }
}