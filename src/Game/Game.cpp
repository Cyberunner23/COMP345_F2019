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
