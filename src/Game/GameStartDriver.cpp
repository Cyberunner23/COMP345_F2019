#include "Map/MapLoader.h"
#include "Deck/Deck.h"
#include <Game\GameState.hpp>

int main(int argc, char** argv)
{
	GameState state;
	MapLoader loader;
	int playerNum;
	int mapSelection;
	std::string mapPath;

	std::cout << "Which map do you want to use: 1, 2, 3 (invalid) or 4 (invalid): ";
	std::cin >> mapSelection;

	switch (mapSelection)
	{
		case 1:
			mapPath = "data/map1.map";
			break;
		case 2:
			mapPath = "data/map2.map";
			break;
		case 3:
			mapPath = "data/map_invalid1.map";
			break;
		case 4:
			mapPath = "data/map_invalid2.map";
			break;
		default:
			std::cout << "Invalid selection, defaulting to map 1"<<std::endl;
			mapPath = "data/map1.map";
			break;
	}

	Map* map = loader.loadMap(mapPath);
	if (map == nullptr)
	{
		std::cout << "Failed to open map!" << std::endl;
	}

	std::cout << "How many players? ";
	while (std::cin >> playerNum && (playerNum < 2 || playerNum > 5)) {
		if (playerNum > 5)
			std::cout << "\nYou cannot play with more than 5 players.";
		else
			std::cout << "\nYou cannot play with less than 2 players.";

		std::cout << "\nPlease enter a valid number of players: ";
	}

	//Creating the players
	state.Players = new std::vector<Player>();
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
		state.Players->push_back(p);
	}

	std::cout<<"Generating the game..."<<std::endl;
	state.GameMap = map;
	state.GameDeck = new Deck();

	std::cout << "Number of players: " << state.Players->size()<<std::endl;

	return 0;
}
