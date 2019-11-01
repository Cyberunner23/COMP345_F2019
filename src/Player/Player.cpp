#include "Player.h"
#include <vector>
#include <iostream>

Player::Player() : Player("", 0, 0, Cities::BLUE, Armies::BLUE) {}

Player::Player(std::string playerName, int playerAge, int playerCoins, Cities cityColor, Armies armyColor)
{
    _name = new std::string(playerName);
    _age = new int(playerAge);
    _coins = new int(playerCoins);
    _bidingFacility = new BidingFacility();
    _hand = new Hand();
    _ownedRegions = new std::vector<Vertex>();
    _numHandCities = new unsigned int(0);
    _numHandArmies = new unsigned int(0);
    _cityColor = new Cities(cityColor);
    _armyColor = new Armies(armyColor);
    _startingRegionID = new unsigned int(0);
}

Player* Player::youngestPlayer(std::vector<Player*> players)
{
    Player* youngestPlayer;
    int youngestAge = *players.at(0)->_age;
    for (auto& player : players) {
    	if (*player->_age < youngestAge) {
    		youngestAge = *player->_age;
    		youngestPlayer = player;
    	}
    }

    return youngestPlayer;
}


Player* Player::bidingWinner(std::vector<Player*> players)
{
	Player* bidingWinner;
	std::vector<Player*> tiedPlayers; //keep a list of players who tied their bid
	int highestBid = findHighestBid(players);

	for (auto& player : players) {
		if (player->_bidingFacility->bid == highestBid)
			tiedPlayers.push_back(player);
	}

	//If more than 2 tiedPlayers than we check for youngest
	if (tiedPlayers.size() > 1)
		return bidingWinner = youngestPlayer(tiedPlayers);

	//highestBid = 0 means all players bid 0
	if (highestBid == 0)
		return bidingWinner = youngestPlayer(players);

	return bidingWinner = tiedPlayers.at(0);
}

int Player::findHighestBid(std::vector<Player*> players)
{
	Player* bidingWinner;
	std::vector<Player*> tiedPlayers; //keep a list of players who tied their bid
	int highestBid = players.at(0)->_bidingFacility->bid;

	for (auto& player : players) {
		if (player->_bidingFacility->bid > highestBid)
			highestBid = player->_bidingFacility->bid;
	}

	return highestBid;
}

void Player::revealBids(std::vector<Player*> players)
{
	for (auto& player : players) {
		std::cout << player->_name << " has bid " << player->_bidingFacility->bid << " _coins." << std::endl;
	}
}


int Player::assignCoinsToPlayers(std::vector<Player>* players, int coins)
{
	for (Player& player : players) {
		*player->getCoins() = coins;
	}

	for (auto it = std::begin(players); it != std::end(players); ++it) {
		std::cout << *it << "\n";
	}

	return coins;
}

//Assigns number of coins to each player depending on their number
int Player::assignCoinsToPlayers(std::vector<Player>* players)
{
	switch (players->size()) {
	case 2:
		return assignCoinsToPlayers(players, 14);
	case 3:
		return assignCoinsToPlayers(players, 11);
	case 4:
		return assignCoinsToPlayers(players, 9);
	case 5:
		return assignCoinsToPlayers(players, 8);
	}
}

//When Player wins a bid he has to pay coins and 
void Player::PayCoin()
{
    _bidingFacility->supply += _bidingFacility->bid;
    _coins -= _bidingFacility->bid;
}
