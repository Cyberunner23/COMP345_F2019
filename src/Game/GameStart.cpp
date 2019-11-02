#include "GameStart.h"
#include "Player/Player.h"

GameStart::GameStart(int PlayerNum, std::string mapPath)
{

	GameState* state = new GameState();
	state->Players = new std::vector<Player>();
	Game = state;

  for(int i = 0; i < PlayerNum; i++)
  {
	  Player p;

	  std::string* name = new std::string("Player " + std::to_string(i+1));
	  int* age = new int();
	  std::cout << "Please enter your age: ";
	  while (std::cin >> *age && (*age < 0) ) {
		  std::cout << "\nPlease enter a valid age: ";
	  }

	  p.setName(name);
	  p.setage(age);

      std::cout << "Adding " << *p.getName() << std::endl;
	  Game->Players->push_back(p);
  }

  std::cout << "Game.players.size() " << Game->Players->size();

  Map* map = loader->loadMap(mapPath);
  if (map == nullptr)
  {
      std::cout << "Failed to open map!" << std::endl;
  }
  Game->GameMap = map;

  //Total outputs: A game state with a map, n players, a shuffled deck, and a starting 6 cards
}

GameState* GameStart::StartGame()
{
  return Game;
}
