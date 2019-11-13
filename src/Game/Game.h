#pragma once

#include <iostream>
#include <vector>
#include "Game/GameState.hpp"
#include "Player/Player.h"

class Game {

public:
    static std::string selectMap();
    static std::vector<Player>* createPlayers();
    static void displayFaceUpCards(GameState state);

    static void PlaceArmiesInCountryStartup(GameState& state);
	static void PlaceArmiesInCountryStartup(GameState& state, CountryNode* startingCountry);
};