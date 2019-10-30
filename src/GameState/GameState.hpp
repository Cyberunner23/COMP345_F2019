#pragma once

#include <vector>

#include "Deck/Deck.h"
#include "Map/Map.h"
#include "Player/Player.h"

struct GameState
{
    Map* GameMap;
    std::vector<Cards>* ShownCards;
    std::vector<Player>* Players;
};
