
#include "Action/Actions.hpp"
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
	p1.setName(nameP1);
	p1.setage(ageP1);
	p1.setCityColor(Cities::BLUE);
	p1.setArmyColor(Armies::BLUE);
	state.Players->push_back(p1);

	Player p2;
	p2.setName(nameP2);
	p2.setage(ageP2);
	p2.setCityColor(Cities::GREEN);
	p2.setArmyColor(Armies::GREEN);
	state.Players->push_back(p2);

	Player p3;
	p3.setName(nameP3);
	p3.setage(ageP3);
	p3.setCityColor(Cities::RED);
	p3.setArmyColor(Armies::RED);
	state.Players->push_back(p3);


	// Create action objects
	std::vector<Actions> playerActions;
	for (auto& player : *state.Players)
	{
		playerActions.emplace_back(&state, &player);
	}

	int turn = 0;
	int cardPosition;

	//Will execute game loop 10 times 
	for (int i = 0; i < 10; i++) {

		//Player selects card position
		std::cout << "Please select a card by entering its position (1 to 6): ";
		while (std::cin >> cardPosition && (cardPosition < 1 || cardPosition > 6)) {
			std::cout << "\nPlease enter a valid position: ";
		}

		//Player take face up card and execute action
		int cardIndex = cardPosition - 1;
		Cards c = state.ShownCards->at((cardIndex));
		std::cout << *state.Players->at(turn % 3).getName() << " has taken the card at position " << cardPosition << ", with action: '" << state.GameDeck->DeckMap->at(c) << "'" << std::endl;
		playerActions.at(turn % 3).RunAction(c);

		//Slide remaining cards to left and draw new card placed in rightmost position
		state.ShownCards->erase(state.ShownCards->begin() + cardIndex);
		state.ShownCards->push_back(state.GameDeck->draw());
		Game::displayFaceUpCards(state);

		//Next player turn
		turn++;
	}

	return 0;
}