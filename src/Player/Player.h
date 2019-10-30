#pragma once

#include <string>
#include "BidingFacility.h"
#include "../Deck/Deck.h"

class Player {

public:
	Player();
	Player(std::string playerName, int playerAge, int playerCoins);
	//countries
	//armies
	//cards
	BidingFacility* bidingFacility;
	std::string name;
	Hand* hand;
	int age;
	int coins;
	static int findHighestBid(std::vector<Player*> players);
	static Player* bidingWinner(std::vector<Player*> players);
	static Player* youngestPlayer(std::vector<Player*> players);
	static void revealBids(std::vector<Player*> players);
	void PayCoin();
	void PlaceNewArmies();
	void MoveArmies();
	void MoveOverLand();
	void BuildCity();
	void DestroyArmy();

};
