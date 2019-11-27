#include "GameState.hpp"
#include "Map/MapLoader.h"
#include "Player/Player.h"

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

	//Creating the players
	state.Players = Game::createPlayers(&state);
	int numOfPlayers = state.Players->size();
	std::cout << "Number of players: " << numOfPlayers << std::endl;

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

	//Players choose their armies & cities color
	Game::chooseArmiesAndCitiesColor(&state);

	//Placing armies in starting country
	Game::PlaceArmiesInCountryStartup(state);

	//Assigning coins to players
	int* assignedCoins = Player::assignCoinsToPlayers(state.Players);
	state.supply = new int(44 - *assignedCoins * numOfPlayers);

	std::cout << "Generating the game..." << std::endl;
	Game::displayGameState(state);
	Player::displayPlayers(&state);

	int turn = getRandomIndex(numOfPlayers); //Randomly selecting first player
	std::cout << "\nFirst player is: " << *state.Players->at(turn).getName() << std::endl;

	int rounds = 0;
	while (!playerReachedMaxNumOfCards(&state)) {
		state.Players->at(turn % numOfPlayers).executeStrategy(state, turn);
		turn++;
	}

	Game::displayGameState(state);
	Game::tournamentResults(&state);

	return 0;
}