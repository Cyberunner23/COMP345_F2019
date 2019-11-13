#pragma once
#include "Game/Game.h"

class GameState;

class PlayerStrategies {

public:
    PlayerStrategies() = default;
    virtual bool execute(GameState state, int trun) = 0;

};


class HumanPlayer : public PlayerStrategies {

public:
    HumanPlayer() = default;
    bool execute(GameState state, int turn) override;
};