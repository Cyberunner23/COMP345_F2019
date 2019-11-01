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
    GameStart();
    GameStart(int PlayerNum, std::string mapPath);
    ~GameStart();
    GameState StartGame();

    MapLoader* loader;
    unsigned* seed;
    GameState* Game;

}
