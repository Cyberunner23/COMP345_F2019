#pragma once

#include <string>

#include "BidingFacility.h"
#include "Deck/Deck.h"
#include "Map/Map.h"
#include "Utils/MapUtil.hpp"
#include "PlayerStrategies.h"
#include "Observer/ObserverBase.h"
#include "ScoreCalculator/ScoreCalculator.h"

class PlayerStrategies;
class GameState;

class Player : public ObserverBase {

private:
	PlayerStrategies* _strategy;
    BidingFacility* _bidingFacility;
    std::string* _name;
    Hand* _hand;
	int* _id;
    int* _age;
    int* _coins;
    int* _score;
	GameState* _subject;

    unsigned int* _startingRegionID;
    std::vector<Vertex>* _ownedRegions;
    unsigned int* _numHandCities;
    unsigned int* _numHandArmies;
    Cities* _cityColor; // Color of the cities for the player
    Armies* _armyColor; // Color of the army for the player

	bool MoveArmies(Map* map, GameState* state, bool canMoveOverWater);
	bool countryIDUserInput(Map* map, unsigned int& countryID, std::string queryText);


public:
    Player();
	Player(GameState* state);
    Player(std::string playerName, int playerAge, int playerCoins, Cities cityColor, Armies armyColor, GameState* state);

    unsigned int getStartingRegionID() {return *_startingRegionID;}
    void setStartingRegionID(unsigned int ID) { *_startingRegionID = ID;}

	PlayerStrategies* getPlayerStrategies() { return _strategy; }
	void setPlayerStrategies(PlayerStrategies* strategy) { _strategy = strategy; }

    BidingFacility* getBidingFacility() {return _bidingFacility;}
    void setBidingFacility(BidingFacility* facility) {_bidingFacility = facility;}

	int* getId() { return _id; }
	void setId(int* id) { _id = id; }

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
    static void displayPlayers(GameState* state);
    void PayCoin(GameState* state);
	bool PayCoin(GameState* state, int cardPosition);

	bool RunAction(Map* map, GameState* state, Card card);
	std::vector<int>* findPlayerCitiesCountryIDs(Map* map);
	std::vector<int>* findPlayerArmiesCountryIDs(Map* map);
	bool PlaceNewArmies(Map* map, GameState* state);
	bool MoveArmies(Map* map, GameState* state);
	bool MoveOverLandOrWater(Map* map, GameState* state);
	bool BuildCity(Map* map, GameState* state);
	bool DestroyArmy(Map* map, GameState* state);
	bool AndOrAction();
	bool Ignore();

	void Update(int id) override;
	void Update() override;
	void DisplayPlayer(int id);
	void CalculateScore();

	bool executeStrategy(GameState state, int turn);
	void changeStrategy();

};

bool playerReachedMaxNumOfCards(GameState* state);
int getRandomIndex(int size);
