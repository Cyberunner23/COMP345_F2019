#pragma once

#include <algorithm>

#include "GameState/GameState.hpp"
#include "Utils/MapUtil.hpp"

// Set of actions the player has, one instance per player
class Actions
{

private:
    GameState* _state;
    Player* _player;

public:
    explicit Actions(GameState* state, Player* player);

    bool PlaceNewArmies();
    bool MoveArmies();
    bool MoveOverLand();
    bool MoveOverWater();
    bool BuildCity();
    bool DestroyArmy();
    bool AndOrAction();
    bool Ignore();
};
