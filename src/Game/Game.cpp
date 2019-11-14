#include "Game.h"

std::string Game::selectMap()
{
	int mapSelection;
	std::string mapPath;

	std::cout << "Which map do you want to use: 1, 2, 3 (invalid) or 4 (invalid): ";
	std::cin >> mapSelection;

	switch (mapSelection)
	{
	case 1:
		return mapPath = "data/map1.map";
	case 2:
		return mapPath = "data/map2.map";
	case 3:
		return mapPath = "data/map_invalid1.map";
	case 4:
		return mapPath = "data/map_invalid2.map";
	default:
		std::cout << "Invalid selection, defaulting to map 1" << std::endl;
		return mapPath = "data/map1.map";
		
	}
}

std::vector<Player>* Game::createPlayers()
{
	int playerNum;
	std::vector<Player>* players = new std::vector<Player>();

	std::cout << "How many players? ";
	while (std::cin >> playerNum && (playerNum < 2 || playerNum > 5)) {
		if (playerNum > 5)
			std::cout << "\nYou cannot play with more than 5 players.";
		else
			std::cout << "\nYou cannot play with less than 2 players.";

		std::cout << "\nPlease enter a valid number of players: ";
	}

	//Creating the players
	for (int i = 0; i < playerNum; i++)
	{
		Player p;

		std::string* name = new std::string("Player " + std::to_string(i + 1));
		int* age = new int();
		std::cout << "Please enter your age: ";
		while (std::cin >> *age && (*age < 0)) {
			std::cout << "\nPlease enter a valid age: ";
		}

		p.setName(name);
		p.setage(age);

		std::cout << "Adding " << *p.getName() << std::endl;
		players->push_back(p);
	}

	return players;
}

void Game::displayFaceUpCards(GameState state)
{
	int position = 1;
	std::cout << "\n------- Displaying Cards -------" << std::endl;
	for (auto& card : *state.ShownCards) {
		std::cout << "Position: " << position << ", Action: " << state.GameDeck->DeckMap->at(card) << std::endl;
		position++;
	}
}

void Game::PlaceArmiesInCountryStartup(GameState& state)
{
    unsigned int startingCountryID = state.GameMap->getStartingCountryID();
    CountryNode* startingCountry = state.GameMap->findCountryByID(startingCountryID);

    if (state.Players->size() == 2)
    {
		int countryID;
		PlaceArmiesInCountryStartup(state, startingCountry);
		Armies newArmy = Armies::WHITE; //thrid non player army
		for (int i = 0; i < 4; i++) { //Place 4 armies to get to 10 armies on the map
			Player player = state.Players->at(i%2);
			std::cout << *player.getName() << ", please enter the country ID where you wanna place the army: ";
			while (std::cin >> countryID && (countryID < 1 || countryID > state.GameMap->getNumCountries())) {
				std::cout << "Invalid ID range ..." << std::endl;
				std::cout << "Please enter a valid country ID: ";
			}
			CountryNode* country = state.GameMap->findCountryByID(countryID);
			country->ArmiesInCountry->push_back(newArmy);
			std::cout << "\n" << *player.getName() << " just placed a new army." << std::endl;
		}
    }
	//More than 3 players
    else
    {
		PlaceArmiesInCountryStartup(state, startingCountry);
    }
}

void Game::PlaceArmiesInCountryStartup(GameState& state, CountryNode* startingCountry)
{
	//Each player placing 3 armies on starting region
	for (auto& player : *state.Players)
	{
		unsigned int numArmies = player.getNumHandArmies();
		numArmies -= 3;
		player.setNumHandArmies(numArmies);

		startingCountry->ArmiesInCountry->push_back(player.getArmyColor());
		startingCountry->ArmiesInCountry->push_back(player.getArmyColor());
		startingCountry->ArmiesInCountry->push_back(player.getArmyColor());

		std::cout << *player.getName() << " has finished placing his 3 armies on the starting region." << std::endl;
	}

	std::cout << "The starting region now contains " << startingCountry->ArmiesInCountry->size() << " armies." << std::endl;
}
