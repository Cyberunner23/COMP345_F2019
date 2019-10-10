#pragma once

#include <Player/BidingFacility.h>
#include <string>

class Player {

public:
	Player(int age, int coins);
	//countries
	//armies
	//cards
	BidingFacility bf;
	std::string name;
	int age;
	int coins;
	void PayCoin(int coins);
	void PlaceNewArmies();
	void MoveArmies();
	void MoveOverLand();
	void BuildCity();
	void DestroyArmy();

};
