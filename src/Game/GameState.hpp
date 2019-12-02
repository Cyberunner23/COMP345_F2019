#pragma once

#include <vector>

#include "Deck/Deck.h"
#include "Map/Map.h"
#include "Player/Player.h"
#include "Observer/Subject.h"

class Player;

struct GameState : public Subject
{
    Deck* GameDeck;
    std::vector<Card>* ShownCards;
    std::vector<Player>* Players;
	int* supply;

	void NotifyObservers(int turn);
	void NotifyObservers();
};

