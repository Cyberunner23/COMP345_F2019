#include "GameStart.h"
#include "Player/Player.h"

GameStart::GameStart(int PlayerNum, std::string mapPath)
{
  unsigned seed;
  seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::shuffle(Game->GameDeck->CardList->begin(), Game->GameDeck->CardList->end(), std::default_random_engine(seed)); //Shuffles the deck when the game start is done

  Game->ShownCards->push_back(Game->GameDeck->draw());
  Game->ShownCards->push_back(Game->GameDeck->draw());
  Game->ShownCards->push_back(Game->GameDeck->draw());
  Game->ShownCards->push_back(Game->GameDeck->draw());
  Game->ShownCards->push_back(Game->GameDeck->draw());
  Game->ShownCards->push_back(Game->GameDeck->draw());


  for(int i = 0; i < PlayerNum; i++)
  {
      Player* p = new Player();
      std::cout << "Adding Player: " << i+1 << std::endl;
      Game->Players->push_back(*p);
  }

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
