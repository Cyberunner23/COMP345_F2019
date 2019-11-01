
#include "Action/Actions.hpp"
#include "Map/MapLoader.h"

int main(int argc, char** argv)
{

    GameState state;

    // Load Map
    std::string mapPath = "data/map1.map";
    MapLoader loader;
    Map* map = loader.loadMap(mapPath);

    if (map == nullptr)
    {
        std::cout << "Failed to open map!" << std::endl;
        return 1;
    }

    state.GameMap = map;

    // Create Deck

    // Create players
    std::vector<Player> players;
    //state.Players

    // Give cards to players

    // Create action objects
    std::vector<Actions> playerActions;
    for(auto& player : players)
    {
        playerActions.emplace_back(&state, &player);
    }

    // Loop through players, make a player do the action for the card


    return 0;
}