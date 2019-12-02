#include "Map/MapLoader.h"
#include "Deck/Deck.h"

#include "Game/GameState.hpp"
#include "Game/Game.h"

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

	std::cout<<"Generating the game..."<<std::endl;
	state.GameDeck = new Deck();

	std::cout << "Number of players: " << state.Players->size()<<std::endl;

	Player::displayPlayers(&state);

	return 0;
}
