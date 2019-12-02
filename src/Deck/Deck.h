#pragma once
#include <string>
#include <iostream>
#include <map>
#include <vector>

#include "Card.h"

enum class Cities
{
    RED,
    WHITE,
    BLUE,
    YELLOW,
    GREEN
};

enum class Armies
{
    RED,
    WHITE,
    BLUE,
    YELLOW,
    GREEN
};

class Deck
{
public:

    Deck();
    ~Deck();

    Card draw();
    void shuffleDeck();

    std::map<Cards, std::string>* DeckMap;
    std::map<Cards, std::string>* GoodsMap;
    std::vector<Card>* CardList; // List of cards in the deck

    std::map<Cities, std::string>* CitiesMap;
    std::map<Armies, std::string>* ArmiesMap;
};

class Hand
{
public:

  Hand();
  ~Hand();
  std::vector<Card>* HandList; //List of cards in your _hand

  void exchange();
};
