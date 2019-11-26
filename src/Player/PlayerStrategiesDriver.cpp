
#include "Game/GameState.hpp"
#include "Game/Game.h"
#include "Map/MapLoader.h"

int main(int argc, char** argv)
{

	GameState state;

	// Load Map
	std::string mapPath = "data/map1.map";
	MapLoader loader;


	if (!loader.loadMap(mapPath))
	{
		std::cout << "Failed to open map!" << std::endl;
		return 1;
	}

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
	std::string* nameP4 = new std::string("Player 4");
	std::string* nameP5 = new std::string("Player 5");

	int* ageP1 = new int(23);
	int* ageP2 = new int(21);
	int* ageP3 = new int(22);
	int* ageP4 = new int(30);
	int* ageP5 = new int(50);


	Player p1(&state);
	p1.setStartingRegionID(Map::GetInstance().getStartingCountryID());
	//p1.setPlayerStrategies(new HumanPlayer());
	p1.setName(nameP1);
	p1.setage(ageP1);
	p1.setCityColor(Cities::BLUE);
	p1.setArmyColor(Armies::BLUE);
	p1.setNumHandArmies(14);
	p1.setNumHandCities(3);
	//state.Players->push_back(p1);

	Player p2(&state);
	p2.setStartingRegionID(Map::GetInstance().getStartingCountryID());
	p2.setPlayerStrategies(new GreedyComputer());
	p2.setName(nameP2);
	p2.setage(ageP2);
	p2.setCityColor(Cities::GREEN);
	p2.setArmyColor(Armies::GREEN);
	p2.setNumHandArmies(14);
	p2.setNumHandCities(3);
	state.Players->push_back(p2);

	Player p3(&state);
	p3.setStartingRegionID(Map::GetInstance().getStartingCountryID());
	p3.setPlayerStrategies(new ModerateComputer());
	p3.setName(nameP3);
	p3.setage(ageP3);
	p3.setCityColor(Cities::RED);
	p3.setArmyColor(Armies::RED);
	p3.setNumHandArmies(14);
	p3.setNumHandCities(3);
	state.Players->push_back(p3);

	Player p4(&state);
	p4.setStartingRegionID(Map::GetInstance().getStartingCountryID());
	p4.setPlayerStrategies(new HumanPlayer());
	p4.setName(nameP4);
	p4.setage(ageP4);
	p4.setCityColor(Cities::WHITE);
	p4.setArmyColor(Armies::WHITE);
	p4.setNumHandArmies(14);
	p4.setNumHandCities(3);
	//state.Players->push_back(p4);

	Player p5(&state);
	p5.setStartingRegionID(Map::GetInstance().getStartingCountryID());
	p5.setPlayerStrategies(new RandomComputer());
	p5.setName(nameP5);
	p5.setage(ageP5);
	p5.setCityColor(Cities::YELLOW);
	p5.setArmyColor(Armies::YELLOW);
	p5.setNumHandArmies(14);
	p5.setNumHandCities(3);
	state.Players->push_back(p5);

	int turn = 0;
	int numOfPlayers = state.Players->size();

	for (int i = 0; i < 30; i++) {
		state.Players->at(turn % numOfPlayers).executeStrategy(state, turn);
		turn++;
	}

	Player::displayPlayers(state.Players);

	Map::GetInstance().dump();

	return 0;
}