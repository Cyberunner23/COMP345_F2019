
#include "Deck/Deck.h"
#include "GameState.hpp"


int main(int argc, char** argv)
{
	GameState state;
	int maxCardsShown = 6;
	int* cardCost = new int();

	state.GameDeck = new Deck(); //Instantiating the Deck
	state.GameDeck->shuffleDeck();//Shuffling the deck

	//Initialize Players
	state.Players = new std::vector<Player>();

	std::string* nameP1 = new std::string("Player 1");
	std::string* nameP2 = new std::string("Player 2");
	std::string* nameP3 = new std::string("Player 3");

	int* ageP1 = new int(23);
	int* ageP2 = new int(21);
	int* ageP3 = new int(22);

	int* coinP1 = new int(2);
	int* coinP2 = new int(6);
	int* coinP3 = new int(3);

	Player p1;
	p1.setName(nameP1);
	p1.setage(ageP1);
	p1.setCityColor(Cities::BLUE);
	p1.setArmyColor(Armies::BLUE);
	p1.setCoins(coinP1);
	state.Players->push_back(p1);

	Player p2;
	p2.setName(nameP2);
	p2.setage(ageP2);
	p2.setCityColor(Cities::GREEN);
	p2.setArmyColor(Armies::GREEN);
	p2.setCoins(coinP2);
	state.Players->push_back(p2);

	Player p3;
	p3.setName(nameP3);
	p3.setage(ageP3);
	p3.setCityColor(Cities::RED);
	p3.setArmyColor(Armies::RED);
	p3.setCoins(coinP3);
	state.Players->push_back(p3);

	//Drawing cards to show face up.
	state.ShownCards = new std::vector<Cards>();
	for (int i = 0; i < maxCardsShown; i++) {

		Cards c = state.GameDeck->draw();
		std::cout << "The card in slot: " << i + 1 << " is " << state.GameDeck->DeckMap->at(c) << std::endl;
		state.ShownCards->push_back(c);

	}

	//The loop of players picking a card to add to their hand
	for (int i = 0; i < state.Players->size(); i++)
	{
		int* playerCoins = state.Players->at(i).getCoins();
		int playerChoice;
		std::cout << "Player " << i + 1 << " please pick a card  to draw (1-6) " << std::endl;
		std::cout << "You have " << *playerCoins << " coins." << std::endl;
		std::cin >> playerChoice;

		//Making sure the player picks a card within the bounds
		while (playerChoice < 1 || playerChoice > 6)
		{
			std::cout << "Invalid choice. Please pick a card from 1-6" << std::endl;
			std::cin >> playerChoice;
		}

		//Setting the cost depending on the player's choice
		switch (playerChoice)
		{
		case 1:
			*cardCost = 0;
			break;
		case 2:
			*cardCost = 1;
			break;
		case 3:
			*cardCost = 1;
			break;
		case 4:
			*cardCost = 2;
			break;
		case 5:
			*cardCost = 2;
			break;
		case 6:
			*cardCost = 3;
			break;
		default: *cardCost = 0;
		}


		//If you can afford the card, purchase it and add it to hand. Otherwise, end turn
		if (*cardCost <= *playerCoins)
		{
			Cards c = state.ShownCards->at(playerChoice - 1);
			Hand* h = state.Players->at(i).getHand();
			*playerCoins = *playerCoins - *cardCost;
			std::cout << "You have purchased " << state.GameDeck->DeckMap->at(c) << std::endl;
			std::cout << "You have " << *playerCoins << " coins remaining" << std::endl;
			h->HandList->push_back(c);
			state.Players->at(i).setHand(h);
			state.ShownCards->at(playerChoice - 1) = state.GameDeck->draw();
		}
		else
		{
			std::cout << "Cannot afford card" << std::endl;
		}

	}


	//Displaying player's hands after one loop
	for (int i = 0; i < state.Players->size(); i++)
	{
		Hand* currentHand = state.Players->at(i).getHand();
		std::cout << "Player " << i + 1 << " your hand is:" << std::endl;
		for (int i = 0; i < currentHand->HandList->size(); i++)
		{
			std::cout << state.GameDeck->DeckMap->at(currentHand->HandList->at(i)) << std::endl;
		}
		std::cout << "and you have " << *state.Players->at(i).getCoins() << " coins remaining" << std::endl;
	}
	//Displaying the new cards on the table

	std::cout << "The cards on the table are: " << std::endl;
	for (int i = 0; i < state.ShownCards->size(); i++)
	{
		std::cout << state.GameDeck->DeckMap->at(state.ShownCards->at(i)) << std::endl;
	}

	Player::displayPlayers(state.Players);

	return 0;
}
