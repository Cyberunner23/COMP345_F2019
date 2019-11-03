#pragma once
#include <string>
#include <iostream>
#include <map>
#include <vector>


//A * in the enum indicates this card is for a 5+ player game. Maybe not be implemented
//https://boardgamegeek.com/article/12349266#12349266 <<List of cards in game
//Total of 42 cards
enum Cards
{
    f1, f2,f3, f4, f5, f6, f7, f8,
    c1, c2, c3, c4, c5, c6, c7, c8, c9, c10,
    a1, a2, a3, a4, a5, a6, a7, a8, a9,
    o1, o2, o3, o4, o5, o6, o7,
    cr1,cr2,cr3,cr4,cr5
};

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

    Cards draw();
	void shuffleDeck();

    std::map<Cards, std::string>* DeckMap;
    std::vector<Cards>* CardList; // List of cards in the deck

    std::map<Cities, std::string>* CitiesMap;
    std::map<Armies, std::string>* ArmiesMap;
};

class Hand
{
public:

  Hand();
  ~Hand();
  std::vector<Cards>* HandList; //List of cards in your _hand

  void exchange();
};
