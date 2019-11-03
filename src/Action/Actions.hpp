#pragma once

#include <algorithm>

#include "Game/GameState.hpp"
#include "Utils/MapUtil.hpp"

// Set of actions the player has, one instance per player
class Actions
{

private:
    GameState* _state;
    Player* _player;

    bool MoveArmies(bool canMoveOverWater);

    // return false if user canceled
    bool countryIDUserInput(unsigned int& countryID, std::string queryText);

public:
    explicit Actions(GameState* state, Player* player);

    bool RunAction(Cards card);

    bool PlaceNewArmies();
    bool MoveArmies();
    bool MoveOverLandOrWater();
    bool BuildCity();
    bool DestroyArmy();
    bool AndOrAction();
    bool Ignore();
};
