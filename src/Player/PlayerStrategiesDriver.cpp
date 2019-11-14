
#include "Game/GameState.hpp"
#include "Game/Game.h"
#include "Map/MapLoader.h"

int main(int argc, char** argv)
{

	GameState state;

	// Load Map
	std::string mapPath = "data/map1.map";
	MapLoader loader;
	Map* map = loader.loadMap(mapPath);

	if (map == nullptr)
	{
		std::cout << "Failed to open map!" << std::endl;
		return 1;
	}

	state.GameMap = map;

	// Create Deck
	state.GameDeck = new Deck();

	//Shuffling deck and drawing 6 cards
	state.GameDeck->shuffleDeck();
	state.ShownCards = new std::vector<Cards>();
	for (int i = 0; i < 6; i++) {
		Cards c = state.GameDeck->draw();
		std::cout << "You Have Drawn: " << state.GameDeck->DeckMap->at(c) << std::endl;
		state.ShownCards->push_back(c);
	}

	// Create players
	state.Players = new std::vector<Player>();
	std::string* nameP1 = new std::string("Player 1");
	std::string* nameP2 = new std::string("Player 2");
	std::string* nameP3 = new std::string("Player 3");

	int* ageP1 = new int(23);
	int* ageP2 = new int(21);
	int* ageP3 = new int(22);

	Player p1;
	p1.setStartingRegionID(map->getStartingCountryID());
	p1.setPlayerStrategies(new HumanPlayer());
	p1.setName(nameP1);
	p1.setage(ageP1);
	p1.setCityColor(Cities::BLUE);
	p1.setArmyColor(Armies::BLUE);
	p1.setNumHandArmies(14);
	p1.setNumHandCities(3);
	state.Players->push_back(p1);

	Player p2;
	p2.setStartingRegionID(map->getStartingCountryID());
	p2.setPlayerStrategies(new GreedyComputer());
	p2.setName(nameP2);
	p2.setage(ageP2);
	p2.setCityColor(Cities::GREEN);
	p2.setArmyColor(Armies::GREEN);
	p2.setNumHandArmies(14);
	p2.setNumHandCities(3);
	state.Players->push_back(p2);

	Player p3;
	p3.setStartingRegionID(map->getStartingCountryID());
	p3.setPlayerStrategies(new ModerateComputer());
	p3.setName(nameP3);
	p3.setage(ageP3);
	p3.setCityColor(Cities::RED);
	p3.setArmyColor(Armies::RED);
	p3.setNumHandArmies(14);
	p3.setNumHandCities(3);
	state.Players->push_back(p3);

	int turn = 0;
	int numOfPlayers = state.Players->size();

	for (int i = 0; i < 10; i++) {
		state.Players->at(turn%numOfPlayers).executeStrategy(state, turn);
		turn++;
	}

	return 0;
}