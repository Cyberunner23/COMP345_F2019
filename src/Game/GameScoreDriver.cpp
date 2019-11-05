
#include "Deck/Deck.h"
#include "GameState.hpp"
#include "ScoreCalculator/ScoreCalculator.h"
#include <Map/MapLoader.h>
#include <Game/Game.h>


int main(int argc, char** argv)
{
    GameState state;
    MapLoader loader;
    std::string mapPath;

    mapPath = Game::selectMap();

    Map *map = loader.loadMap(mapPath);
    if (map == nullptr)
    {
        std::cout << "Failed to open map!" << std::endl;
    }

    std::cout << "Generating the game..." << std::endl;
    state.GameMap = map;

    state.GameDeck = new Deck(); //Instantiating the Deck
    state.GameDeck->shuffleDeck();//Shuffling the deck

    //Initialize Players
    state.Players = new std::vector<Player>();

    std::string *nameP1 = new std::string("Player 1");
    std::string *nameP2 = new std::string("Player 2");
    std::string *nameP3 = new std::string("Player 3");

    int *ageP1 = new int(23);
    int *ageP2 = new int(21);
    int *ageP3 = new int(22);

    int *coinP1 = new int(2);
    int *coinP2 = new int(6);
    int *coinP3 = new int(3);

    Player p1;
    p1.setName(nameP1);
    p1.setage(ageP1);
    p1.setCityColor(Cities::BLUE);
    p1.setArmyColor(Armies::BLUE);
    p1.setCoins(coinP1);
    p1.getHand()->HandList->push_back(c6);

    Player p2;
    p2.setName(nameP2);
    p2.setage(ageP2);
    p2.setCityColor(Cities::GREEN);
    p2.setArmyColor(Armies::GREEN);
    p2.setCoins(coinP2);

    p2.getHand()->HandList->push_back(cr3);
    p2.getHand()->HandList->push_back(a1);
    p2.getHand()->HandList->push_back(o2);
    p2.getHand()->HandList->push_back(c3);
    p2.getHand()->HandList->push_back(a6);
    p2.getHand()->HandList->push_back(a8);
    p2.getHand()->HandList->push_back(cr5);
    p2.getHand()->HandList->push_back(a9);
    p2.getHand()->HandList->push_back(o1);
    p2.getHand()->HandList->push_back(cr2);
    p2.getHand()->HandList->push_back(f6);
    p2.getHand()->HandList->push_back(f7);
    p2.getHand()->HandList->push_back(o4);

    Player p3;
    p3.setName(nameP3);
    p3.setage(ageP3);
    p3.setCityColor(Cities::RED);
    p3.setArmyColor(Armies::RED);
    p3.setCoins(coinP3);

    p3.getHand()->HandList->push_back(c1);
    p3.getHand()->HandList->push_back(a3);
    p3.getHand()->HandList->push_back(o3);
    p3.getHand()->HandList->push_back(a4);
    p3.getHand()->HandList->push_back(c8);
    p3.getHand()->HandList->push_back(f5);
    p3.getHand()->HandList->push_back(f1);
    p3.getHand()->HandList->push_back(f8);
    p3.getHand()->HandList->push_back(a2);
    p3.getHand()->HandList->push_back(c9);
    p3.getHand()->HandList->push_back(a7);


    state.Players->push_back(p1);
    state.Players->push_back(p2);
    state.Players->push_back(p3);

    //Retrieving 4 countries
    CountryNode *country1 = state.GameMap->findCountryByID(3);
    CountryNode *country2 = state.GameMap->findCountryByID(6);
    CountryNode *country3 = state.GameMap->findCountryByID(5);
    CountryNode *country4 = state.GameMap->findCountryByID(1);

    //Adding armies to countries
    country1->ArmiesInCountry->push_back(p1.getArmyColor());
    country1->ArmiesInCountry->push_back(p1.getArmyColor());

    country2->ArmiesInCountry->push_back(p3.getArmyColor());
    country2->ArmiesInCountry->push_back(p2.getArmyColor());
    country2->ArmiesInCountry->push_back(p2.getArmyColor());

    country3->ArmiesInCountry->push_back(p3.getArmyColor());
    country3->ArmiesInCountry->push_back(p3.getArmyColor());

    country4->ArmiesInCountry->push_back(p1.getArmyColor());
    country4->ArmiesInCountry->push_back(p3.getArmyColor());
    country4->ArmiesInCountry->push_back(p2.getArmyColor());

    ScoreCalculator sc(&state);
    sc.CalculateScores();

    std::cout << "Score for Player 1 should have been 2" << std::endl;
    std::cout << "Score for Player 2 should have been 9" << std::endl;
    std::cout << "Score for Player 3 should have been 17" << std::endl;

    std::cout << "Player 3 should have won" << std::endl;

    return 0;
}
