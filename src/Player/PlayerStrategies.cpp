#include <random>
#include "PlayerStrategies.h"

bool HumanPlayer::execute(GameState state, int turn)
    {
		std::cout << "It's now " << *state.Players->at(turn % state.Players->size()).getName() << " (Human Player) turn... " << std::endl;
	
		int cardPosition;
        //Player selects card position
        std::cout << *state.Players->at(turn % state.Players->size()).getName() << " (Human Player), please select a card by entering its position (1 to 6): ";
        while (std::cin >> cardPosition && (cardPosition < 1 || cardPosition > 6))
        {
            std::cout << "\nPlease enter a valid position: ";
        }

		bool didActionRun = false;

		if (state.Players->at(turn % state.Players->size()).PayCoin(&state, cardPosition))
		{
			//Player take face up card and execute action
			int cardIndex = cardPosition - 1;
			Cards c = state.ShownCards->at((cardIndex));
			std::cout << *state.Players->at(turn % state.Players->size()).getName() << " (Human Player) has taken the card at position " << cardPosition
				<< ", with action: '" << state.GameDeck->DeckMap->at(c) << "'" << std::endl;
			state.Players->at(turn % state.Players->size()).getHand()->HandList->push_back(c);
			didActionRun = state.Players->at(turn % state.Players->size()).RunAction(&Map::GetInstance(), &state, c);

			//Slide remaining cards to left and draw new card placed in rightmost position
			state.ShownCards->erase(state.ShownCards->begin() + cardIndex);
			state.ShownCards->push_back(state.GameDeck->draw());
		}

		//state.Players->at(turn % state.Players->size()).changeStrategy();
        Game::displayFaceUpCards(state);

        return didActionRun;
    }

bool GreedyComputer::execute(GameState state, int turn)
{
	std::cout << "It's now " << *state.Players->at(turn % state.Players->size()).getName() << " (Greedy Computer) turn... " << std::endl;

	//Finding index of first corresponding card
	int cardIndex = findBuildCityOrDestroyArmies(state);
	int cardPosition = cardIndex + 1;

	bool didActionRun = false;

	if (state.Players->at(turn % state.Players->size()).PayCoin(&state, cardPosition))
	{
		//Player take face up card and execute action
		int cardIndex = cardPosition - 1;
		Cards c = state.ShownCards->at((cardIndex));
		std::cout << *state.Players->at(turn % state.Players->size()).getName() << " (Greedy Computer) has taken the card at position " << cardPosition
			<< ", with action: '" << state.GameDeck->DeckMap->at(c) << "'" << std::endl;
		state.Players->at(turn % state.Players->size()).getHand()->HandList->push_back(c);
		didActionRun = state.Players->at(turn % state.Players->size()).RunAction(&Map::GetInstance(), &state, c);

		//Slide remaining cards to left and draw new card placed in rightmost position
		state.ShownCards->erase(state.ShownCards->begin() + cardIndex);
		state.ShownCards->push_back(state.GameDeck->draw());
	}
	
	//state.Players->at(turn % state.Players->size()).changeStrategy();
	Game::displayFaceUpCards(state);

	return didActionRun;
}

bool ModerateComputer::execute(GameState state, int turn)
{
	std::cout << "It's now " << *state.Players->at(turn % state.Players->size()).getName() << " (Moderate Computer) turn... " << std::endl;

	//Finding index of first corresponding card
	int cardIndex = findAddArmies(state);
	int cardPosition = cardIndex + 1;

	bool didActionRun = false;

	if (state.Players->at(turn % state.Players->size()).PayCoin(&state, cardPosition))
	{
		//Player take face up card and execute action
		int cardIndex = cardPosition - 1;
		Cards c = state.ShownCards->at((cardIndex));
		std::cout << *state.Players->at(turn % state.Players->size()).getName() << " (Moderate Computer) has taken the card at position " << cardPosition
			<< ", with action: '" << state.GameDeck->DeckMap->at(c) << "'" << std::endl;
		state.Players->at(turn % state.Players->size()).getHand()->HandList->push_back(c);
		didActionRun = state.Players->at(turn % state.Players->size()).RunAction(&Map::GetInstance(), &state, c);

		//Slide remaining cards to left and draw new card placed in rightmost position
		state.ShownCards->erase(state.ShownCards->begin() + cardIndex);
		state.ShownCards->push_back(state.GameDeck->draw());
	}
	
	//state.Players->at(turn % state.Players->size()).changeStrategy();
	Game::displayFaceUpCards(state);

	return didActionRun;
}

bool RandomComputer::execute(GameState state, int turn)
{
	std::cout << "It's now " << *state.Players->at(turn % state.Players->size()).getName() << " (Random Computer) turn... " << std::endl;

	//Get random card index
	int cardIndex = getRandomCardIndex();
	int cardPosition = cardIndex + 1;

	bool didActionRun = false;

	if (state.Players->at(turn % state.Players->size()).PayCoin(&state, cardPosition))
	{
		//Player take face up card and execute action
		int cardIndex = cardPosition - 1;
		Cards c = state.ShownCards->at((cardIndex));
		std::cout << *state.Players->at(turn % state.Players->size()).getName() << " (Random Computer) has taken the card at position " << cardPosition
			<< ", with action: '" << state.GameDeck->DeckMap->at(c) << "'" << std::endl;
		state.Players->at(turn % state.Players->size()).getHand()->HandList->push_back(c);
		didActionRun = state.Players->at(turn % state.Players->size()).RunAction(&Map::GetInstance(), &state, c);

		//Slide remaining cards to left and draw new card placed in rightmost position
		state.ShownCards->erase(state.ShownCards->begin() + cardIndex);
		state.ShownCards->push_back(state.GameDeck->draw());
	}

	//state.Players->at(turn % state.Players->size()).changeStrategy();
	Game::displayFaceUpCards(state);

	return didActionRun;
}

int findBuildCityOrDestroyArmies(GameState state)
{
	for (int cardIndex = 0; cardIndex < state.ShownCards->size(); cardIndex++) {
		Cards c = state.ShownCards->at((cardIndex));
		//Checks if card action contains 'Destroy Army' or 'Build City' 
		if (state.GameDeck->DeckMap->at(c).find("Destroy 1 Army") != std::string::npos || state.GameDeck->DeckMap->at(c).find("Build City") != std::string::npos)
			return cardIndex;
	}

	//If no card is found then greedy computer will choose a random card
	return getRandomCardIndex();
}

int findAddArmies(GameState state)
{
	for (int cardIndex = 0; cardIndex < state.ShownCards->size(); cardIndex++) {
		Cards c = state.ShownCards->at((cardIndex));
		//Checks if card action contains 'Add' 
		if (state.GameDeck->DeckMap->at(c).find("Add") != std::string::npos)
			return cardIndex;
	}

	//If no 'Add Armies' card, moderate computer will look for a 'Move Armies' card to control region
	return findMoveArmies(state);
}

int findMoveArmies(GameState state)
{
	for (int cardIndex = 0; cardIndex < state.ShownCards->size(); cardIndex++) {
		Cards c = state.ShownCards->at((cardIndex));
		//Checks if card action contains 'Move' 
		if (state.GameDeck->DeckMap->at(c).find("Move") != std::string::npos)
			return cardIndex;
	}

	//If no 'Move Armies' card is found, moderate computer will choose a random card
	return getRandomCardIndex();
}

//Generating random number between 0 and 5 for cardIndex
int getRandomCardIndex() {
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 5); // distribution in range [0, 5]
	return dist6(rng);
}
