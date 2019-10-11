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
	Player* youngestPlayer;
	int youngestAge = players.at(0)->age;
	for (auto& player : players) {
		if (player->age < youngestAge) {
			youngestAge = player->age;
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
		if (player->bidingFacility->bid == highestBid)
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
	int highestBid = players.at(0)->bidingFacility->bid;

	for (auto& player : players) {
		if (player->bidingFacility->bid > highestBid)
			highestBid = player->bidingFacility->bid;
	}

	return highestBid;
}

void Player::revealBids(std::vector<Player*> players)
{
	for (auto& player : players) {
		std::cout << player->name << " has bid " << player->bidingFacility->bid << " coins." << std::endl;
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
