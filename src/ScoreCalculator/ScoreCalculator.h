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
  std::vector<int>* Scores;
  int* currentScore;
  std::vector<Cards>* currentHand;

  int* Forests;
  int* Carrots;
  int* Anvils;
  int* Ores;
  int* Crystals;

  void CalculateScores();
}
