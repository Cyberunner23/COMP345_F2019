
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

	Map* map = loader.loadMap(mapPath);
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

	std::string* nameP1 = new std::string("Player 1");
	std::string* nameP2 = new std::string("Player 2");
	std::string* nameP3 = new std::string("Player 3");

	int* ageP1 = new int(23);
	int* ageP2 = new int(21);
	int* ageP3 = new int(22);

	int* coinP1 = new int(2);
	int* coinP2 = new int(6);
	int* coinP3 = new int(3);

	Player p1;
	p1.setName(nameP1);
	p1.setage(ageP1);
	p1.setCityColor(Cities::BLUE);
	p1.setArmyColor(Armies::BLUE);
	p1.setCoins(coinP1);
	for (int i = 0; i < 10; i++) { //Gives 6 cards to Player 1
		Cards c = state.GameDeck->draw();
		p1.getHand()->HandList->push_back(c);
	}

	Player p2;
	p2.setName(nameP2);
	p2.setage(ageP2);
	p2.setCityColor(Cities::GREEN);
	p2.setArmyColor(Armies::GREEN);
	p2.setCoins(coinP2);
	for (int i = 0; i < 13; i++) { //Gives 9 cards to Player 2
		Cards c = state.GameDeck->draw();
		p2.getHand()->HandList->push_back(c);
	}

	Player p3;
	p3.setName(nameP3);
	p3.setage(ageP3);
	p3.setCityColor(Cities::RED);
	p3.setArmyColor(Armies::RED);
	p3.setCoins(coinP3);
	for (int i = 0; i < 11; i++) { //Give 4 cards to Player 3
		Cards c = state.GameDeck->draw();
		p3.getHand()->HandList->push_back(c);
	}

	state.Players->push_back(p1);
	state.Players->push_back(p2);
	state.Players->push_back(p3);

	//Retrieving 4 countries
	CountryNode* country1 = state.GameMap->findCountryByID(3);
	CountryNode* country2 = state.GameMap->findCountryByID(6);
	CountryNode* country3 = state.GameMap->findCountryByID(5);
	CountryNode* country4 = state.GameMap->findCountryByID(1);

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

	return 0;
}
