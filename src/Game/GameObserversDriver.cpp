
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

	int* ageP1 = new int(23);
	int* ageP2 = new int(21);
	int* ageP3 = new int(22);

	Player p1(&state);
	p1.setId(new int(1));
	p1.setStartingRegionID(Map::GetInstance().getStartingCountryID());
	p1.setName(nameP1);
	p1.setage(ageP1);
	p1.setCityColor(Cities::BLUE);
	p1.setArmyColor(Armies::BLUE);
	p1.setNumHandArmies(14);
	p1.setNumHandCities(3);
	state.Players->push_back(p1);

	Player p2(&state);
	p2.setId(new int(2));
	p2.setStartingRegionID(Map::GetInstance().getStartingCountryID());
	p2.setName(nameP2);
	p2.setage(ageP2);
	p2.setCityColor(Cities::GREEN);
	p2.setArmyColor(Armies::GREEN);
	p2.setNumHandArmies(14);
	p2.setNumHandCities(3);
	state.Players->push_back(p2);

	Player p3(&state);
	p3.setId(new int(3));
	p3.setStartingRegionID(Map::GetInstance().getStartingCountryID());
	p3.setName(nameP3);
	p3.setage(ageP3);
	p3.setCityColor(Cities::RED);
	p3.setArmyColor(Armies::RED);
	p3.setNumHandArmies(14);
	p3.setNumHandCities(3);
	state.Players->push_back(p3);

	int turn = 0;
	int cardPosition;

	//Will execute game loop 3 times 
	for (int i = 0; i < 3; i++) {

		//Player selects card position
		std::cout << "Please select a card by entering its position (1 to 6): ";
		while (std::cin >> cardPosition && (cardPosition < 1 || cardPosition > 6)) {
			std::cout << "\nPlease enter a valid position: ";
		}

		//Player take face up card and execute action
		int cardIndex = cardPosition - 1;
		Cards c = state.ShownCards->at((cardIndex));
		state.Players->at(turn % 3).getHand()->HandList->push_back(c);
		state.NotifyObservers(turn%3 + 1); //turn%3 + 1 is equal to the player's id

		//Slide remaining cards to left and draw new card placed in rightmost position
		state.ShownCards->erase(state.ShownCards->begin() + cardIndex);
		state.ShownCards->push_back(state.GameDeck->draw());
		Game::displayFaceUpCards(state);

		//Next player turn
		turn++;
	}

	Player::displayPlayers(state.Players);

	//Map::GetInstance().dump();

	return 0;
}