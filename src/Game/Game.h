#pragma once

#include <iostream>
#include <vector>
#include <Player/Player.h>
#include "Game/GameState.hpp"

class Player;
struct GameState;

class Game {

public:
    static std::string selectMap();
    static std::vector<Player>* createPlayers();
    static void displayFaceUpCards(GameState state);

    static void PlaceArmiesInCountryStartup(GameState& state);
	static void PlaceArmiesInCountryStartup(GameState& state, CountryNode* startingCountry);
};