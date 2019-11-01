#include "GameStart.h"
#include "Player/Player.h"



GameStart::GameStart()
{

}

GameStart::GameStart(int PlayerNum, std::string mapPath)
{

  seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::shuffle(Game.GameDeck.CardList->begin(), Game.GameDeck.CardList->end(), std::default_random_engine(seed)); //Shuffles the deck when the game start is done

  Game->ShownCards = {Game->GameDeck->draw(), Game->GameDeck->draw(), Game.GameDeck->draw(), Game->GameDeck->draw(), Game->GameDeck->draw(), Game->GameDeck->draw()};
  shownCards->at (0) = 0;
  shownCards->at (1) = 1;
  shownCards->at (2)] = 1;
  shownCards->at (3) = 2;
  shownCards->at (4) = 2;
  shownCards->at (5) = 3;

  for(int i = 0; i < PlayerNum; i++)
  {
      std::cout << "Adding Player: " << i+1 << std::endl;
      Game->Players->push_back(new Player());
  }

  Map map = loader->loader.loadMap(mapPath);
  if (map == nullptr)
  {
      std::cout << "Failed to open map!" << std::endl;
      return 1;
  }
  Game->GameMap = map;

  //Total outputs: A game state with a map, n players, a shuffled deck, and a starting 6 cards
}

GameState GameStart::StartGame()
{

  return Game;
}
