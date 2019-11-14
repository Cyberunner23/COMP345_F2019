#pragma once

#include <string>

#include "BidingFacility.h"
#include "Deck/Deck.h"
#include "Map/Map.h"
#include "Utils/MapUtil.hpp"
#include "PlayerStrategies.h"

class PlayerStrategies;
class GameState;

class Player {

private:
	PlayerStrategies* _strategy;
    BidingFacility* _bidingFacility;
    std::string* _name;
    Hand* _hand;
    int* _age;
    int* _coins;
    int* _score;

    unsigned int* _startingRegionID;
    std::vector<Vertex>* _ownedRegions;
    unsigned int* _numHandCities;
    unsigned int* _numHandArmies;
    Cities* _cityColor; // Color of the cities for the player
    Armies* _armyColor; // Color of the army for the player
	
	bool MoveArmies(Map* map, bool canMoveOverWater);
	bool countryIDUserInput(Map* map, unsigned int& countryID, std::string queryText);


public:
    Player();
    Player(std::string playerName, int playerAge, int playerCoins, Cities cityColor, Armies armyColor);

    unsigned int getStartingRegionID() {return *_startingRegionID;}
    void setStartingRegionID(unsigned int ID) { *_startingRegionID = ID;}

	PlayerStrategies* getPlayerStrategies() { return _strategy; }
	void setPlayerStrategies(PlayerStrategies* strategy) { _strategy = strategy; }

    BidingFacility* getBidingFacility() {return _bidingFacility;}
    void setBidingFacility(BidingFacility* facility) {_bidingFacility = facility;}

    std::string* getName() {return _name;}
    void setName(std::string* name) { _name = name;}

    Hand* getHand() {return _hand;}
    void setHand(Hand* hand) {_hand = hand;}

    int* getage() {return _age;}
    void setage(int* age) {_age = age;}

    int* getCoins() {return _coins;}
    void setCoins(int* coins) {_coins = coins;}

    int* getScore(){return _score;}
    void setScore(int* score){_score = score; }

    std::vector<Vertex>* getOwnedRegions() {return _ownedRegions;}
    void setOwnedRegions(std::vector<Vertex>* ownedRegions) {_ownedRegions = ownedRegions;}

    unsigned int getNumHandCities() {return *_numHandCities;}
    void setNumHandCities(unsigned int handCities) {*_numHandCities = handCities;}

    unsigned int getNumHandArmies() {return *_numHandArmies;}
    void setNumHandArmies(unsigned int handArmies) {*_numHandArmies = handArmies;}

    Cities getCityColor() {return *_cityColor;}
    void setCityColor(Cities color) {*_cityColor = color;}

    Armies getArmyColor() {return *_armyColor;}
    void setArmyColor(Armies color) {*_armyColor = color;}

    static int* findHighestBid(std::vector<Player>* players);
    static Player bidingWinner(std::vector<Player>* players);
    static Player youngestPlayer(std::vector<Player>* players);
    static void revealBids(std::vector<Player>* players);
    static int* assignCoinsToPlayers(std::vector<Player>* players, int* coins);
    static int* assignCoinsToPlayers(std::vector<Player>* players);
    static void displayPlayers(std::vector<Player>* players);
    void PayCoin();

	bool RunAction(Map* map, Deck* deck, Cards card);
	bool PlaceNewArmies(Map* map);
	bool MoveArmies(Map* map);
	bool MoveOverLandOrWater(Map* map);
	bool BuildCity(Map* map);
	bool DestroyArmy(Map* map, Deck* deck);
	bool AndOrAction();
	bool Ignore();

	bool executeStrategy(GameState state, int turn);
	void changeStrategy();

};
