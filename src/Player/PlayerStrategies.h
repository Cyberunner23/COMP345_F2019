#pragma once
#include "Game/Game.h"

class GameState;

class PlayerStrategies {

public:
    PlayerStrategies() = default;
    virtual bool execute(GameState state, int turn) = 0;

};


class HumanPlayer : public PlayerStrategies {

public:
    HumanPlayer() = default;
    bool execute(GameState state, int turn) override;
};

class GreedyComputer : public PlayerStrategies {

public:
	GreedyComputer() = default;
	bool execute(GameState state, int turn) override;
};

class ModerateComputer : public PlayerStrategies {

public:
	ModerateComputer() = default;
	bool execute(GameState state, int turn) override;
};

class RandomComputer : public PlayerStrategies {

public:
	RandomComputer() = default;
	bool execute(GameState state, int turn) override;
};

int findBuildCityOrDestroyArmies(GameState state);
int findAddArmies(GameState state);
int findMoveArmies(GameState state);
int getRandomCardIndex();