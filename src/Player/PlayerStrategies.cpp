#include "PlayerStrategies.h"

bool HumanPlayer::execute(GameState state, int turn)
    {
        int cardPosition;
        //Player selects card position
        std::cout << "Please select a card by entering its position (1 to 6): ";
        while (std::cin >> cardPosition && (cardPosition < 1 || cardPosition > 6))
        {
            std::cout << "\nPlease enter a valid position: ";
        }

        //Player take face up card and execute action
        int cardIndex = cardPosition - 1;
        Cards c = state.ShownCards->at((cardIndex));
        std::cout << *state.Players->at(turn % 3).getName() << " has taken the card at position " << cardPosition
                  << ", with action: '" << state.GameDeck->DeckMap->at(c) << "'" << std::endl;
        bool didActionRun = state.Players->at(turn % 3).RunAction(state.GameMap, state.GameDeck, c);

        //Slide remaining cards to left and draw new card placed in rightmost position
        state.ShownCards->erase(state.ShownCards->begin() + cardIndex);
        state.ShownCards->push_back(state.GameDeck->draw());
        Game::displayFaceUpCards(state);

        //Next player turn
        turn++;

        return didActionRun;
    }
