
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

    if (!loader.loadMap(mapPath))
    {
        std::cout << "Failed to open map!" << std::endl;
    }

    std::cout << "Generating the game..." << std::endl;

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
    p1.getHand()->HandList->push_back(CardFactory::CreateCard(c6));

    Player p2;
    p2.setName(nameP2);
    p2.setage(ageP2);
    p2.setCityColor(Cities::GREEN);
    p2.setArmyColor(Armies::GREEN);
    p2.setCoins(coinP2);

    p2.getHand()->HandList->push_back(CardFactory::CreateCard(cr3));
    p2.getHand()->HandList->push_back(CardFactory::CreateCard(a1));
    p2.getHand()->HandList->push_back(CardFactory::CreateCard(o2));
    p2.getHand()->HandList->push_back(CardFactory::CreateCard(c3));
    p2.getHand()->HandList->push_back(CardFactory::CreateCard(a6));
    p2.getHand()->HandList->push_back(CardFactory::CreateCard(a8));
    p2.getHand()->HandList->push_back(CardFactory::CreateCard(cr5));
    p2.getHand()->HandList->push_back(CardFactory::CreateCard(a9));
    p2.getHand()->HandList->push_back(CardFactory::CreateCard(o1));
    p2.getHand()->HandList->push_back(CardFactory::CreateCard(cr2));
    p2.getHand()->HandList->push_back(CardFactory::CreateCard(f6));
    p2.getHand()->HandList->push_back(CardFactory::CreateCard(f7));
    p2.getHand()->HandList->push_back(CardFactory::CreateCard(o4));

    Player p3;
    p3.setName(nameP3);
    p3.setage(ageP3);
    p3.setCityColor(Cities::RED);
    p3.setArmyColor(Armies::RED);
    p3.setCoins(coinP3);

    p3.getHand()->HandList->push_back(CardFactory::CreateCard(c1));
    p3.getHand()->HandList->push_back(CardFactory::CreateCard(a3));
    p3.getHand()->HandList->push_back(CardFactory::CreateCard(o3));
    p3.getHand()->HandList->push_back(CardFactory::CreateCard(a4));
    p3.getHand()->HandList->push_back(CardFactory::CreateCard(c8));
    p3.getHand()->HandList->push_back(CardFactory::CreateCard(f5));
    p3.getHand()->HandList->push_back(CardFactory::CreateCard(f1));
    p3.getHand()->HandList->push_back(CardFactory::CreateCard(f8));
    p3.getHand()->HandList->push_back(CardFactory::CreateCard(a2));
    p3.getHand()->HandList->push_back(CardFactory::CreateCard(c9));
    p3.getHand()->HandList->push_back(CardFactory::CreateCard(a7));


    state.Players->push_back(p1);
    state.Players->push_back(p2);
    state.Players->push_back(p3);

    //Retrieving 4 countries
    CountryNode *country1 = Map::GetInstance().findCountryByID(3);
    CountryNode *country2 = Map::GetInstance().findCountryByID(6);
    CountryNode *country3 = Map::GetInstance().findCountryByID(5);
    CountryNode *country4 = Map::GetInstance().findCountryByID(1);

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

	delete nameP1;
	delete nameP2;
	delete nameP3;
	delete ageP1;
	delete ageP2;
	delete ageP3;
	delete coinP1;
	delete coinP2;
	delete coinP3;

    return 0;
}
