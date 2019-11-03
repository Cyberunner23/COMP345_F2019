#include "Map/MapLoader.h"
#include "Deck/Deck.h"
#include <Game\GameState.hpp>
#include <Game\Game.h>

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

	//Creating the players
	state.Players = Game::createPlayers();

	std::cout<<"Generating the game..."<<std::endl;
	state.GameMap = map;
	state.GameDeck = new Deck();

	std::cout << "Number of players: " << state.Players->size()<<std::endl;

	delete map;

	return 0;
}
