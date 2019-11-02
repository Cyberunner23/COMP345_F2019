#pragma once
#include "GameState/GameState.hpp"
#include "Deck/Deck.h"
#include <chrono>
#include <random>
#include <iostream>
#include "Map/MapLoader.h"


class GameStart
{
  public:

    GameStart(int PlayerNum, std::string mapPath);
    GameState* StartGame();

    MapLoader* loader;
    GameState* Game;

};
