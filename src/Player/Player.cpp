#include "Player.h"
#include <vector>
#include <iostream>

Player::Player()
{
	name = "";
	age = 0;
	coins = 0;
	bidingFacility = new BidingFacility();
}

Player::Player(std::string playerName, int playerAge, int playerCoins)
{
	name = playerName;
	age = playerAge;
	coins = playerCoins;
	bidingFacility = new BidingFacility();
}

Player* Player::youngestPlayer(std::vector<Player*> players)
{
	Player* youngestPlayer = new Player();
	int youngestAge = players.at(0)->age;
	for (std::vector<Player*>::iterator it = players.begin(); it != players.end(); ++it) {
		if ((*it)->age < youngestAge) {
			youngestAge = (*it)->age;
			youngestPlayer = *it;
		}
	}

	return youngestPlayer;
}


Player* Player::bidingWinner(std::vector<Player*> players)
{
	Player* bidingWinner = new Player();
	std::vector<Player*> tiedPlayers; //keep a list of players who tied their bid
	int highestBid = findHighestBid(players);

	for (std::vector<Player*>::iterator it = players.begin(); it != players.end(); ++it) {
		if ((*it)->bidingFacility->bid == highestBid)
			tiedPlayers.push_back(*it);
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
	Player* bidingWinner = new Player();
	std::vector<Player*> tiedPlayers; //keep a list of players who tied their bid
	int highestBid = players.at(0)->bidingFacility->bid;

	for (std::vector<Player*>::iterator it = players.begin(); it != players.end(); ++it) {
		if ((*it)->bidingFacility->bid > highestBid)
			highestBid = (*it)->bidingFacility->bid;
	}

	return highestBid;
}

void Player::revealBids(std::vector<Player*> players)
{
	for (std::vector<Player*>::iterator it = players.begin(); it != players.end(); ++it) {
		std::cout << (*it)->name << " has bid " << (*it)->bidingFacility->bid << " coins." << std::endl;
	}
}

//When Player wins a bid he has to pay coins and pu
void Player::PayCoin()
{
	bidingFacility->supply += bidingFacility->bid;
	coins -= bidingFacility->bid;
}

void Player::PlaceNewArmies()
{
}

void Player::MoveArmies()
{
}

void Player::MoveOverLand()
{
}

void Player::BuildCity()
{
}

void Player::DestroyArmy()
{
}
