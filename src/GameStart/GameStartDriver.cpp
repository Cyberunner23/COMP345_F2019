#include "GameStart.h"
#include "Deck/Deck.h"

int main(int argc, char** argv)
{
  GameStart game;
  GameState state;
  Deck deck;
  int playerNum;
  int mapSelection;
  std::string mapPath;

  std::cout << "How many players?: "<< std::endl;
  std::cin >> playerNum;

  std::cout << "Which map do you want to use: 1, 2, 3 (invalid) or 4 (invalid)" << std::endl;
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


  std::cout<<"Generating the game..."
  game.GameStart(3, mapPath);
  state = game.StartGame();

  std::cout << "Number of players: " << state.Game->Players->size()<<std::endl;
  std::cout << "Starting Cards:"
  for(int i = 0; i < state.Game->ShownCards->size(); i++)
  {
      std::cout<<deck.DeckMap->at(state.Game->shownCards->at(i)) <<std::endl; //Outputs the cards showing on the table
  }

  return 0;
}
