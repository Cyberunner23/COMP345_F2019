#pragma once
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <Deck/Deck.h>
#include <Game/GameState.hpp>


class ScoreCalculator
{
public:

  ScoreCalculator(GameState* s);

  GameState* State;
  /*int* currentScore;
  std::vector<Cards>* currentHand;
  std::vector<Armies>* regionScores;

  int* Forests;
  int* Carrots;
  int* Anvils;
  int* Ores;
  int* Crystals;*/

  Player CalculateScores();
};
