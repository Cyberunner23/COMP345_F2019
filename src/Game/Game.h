#pragma once

#include <iostream>
#include <vector>
#include <Map/MapLoader.h>
#include <Player/Player.h>
#include "Game/GameState.hpp"

class Player;
struct GameState;

class Game {

private:
	static Armies getArmyColorWithUserInput(int colorChoosen);
	static Cities getCityColorWithUserInput(int colorChoosen);
	static bool isArmyAndCityColorAvailable(GameState* state, Armies armyColor, Cities cityColor);

public:
    static std::string selectMap();
    static std::vector<Player>* createPlayers(GameState* state);
    static void displayFaceUpCards(GameState state);
	static void displayGameState(GameState state);
	static void selectStrategy(Player* p);
	static void chooseArmiesAndCitiesColor(GameState* state);

    static void PlaceArmiesInCountryStartup(GameState& state);
	static void PlaceArmiesInCountryStartup(GameState& state, CountryNode* startingCountry);

	static void tournamentResults(GameState* state);
};