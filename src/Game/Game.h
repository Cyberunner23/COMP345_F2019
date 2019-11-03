#pragma once

#include <iostream>
#include <vector>
#include "Player/Player.h"

class Game {

	public:
		static std::string selectMap();
		static std::vector<Player>* createPlayers();
};