#include "Deck.h"

int main() {

    Deck deck;
    Hand hand;
    std::string response;

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(deck.CardList->begin(), deck.CardList->end(), std::default_random_engine(seed));

    Cards c = deck.draw();
    hand.HandList->push_back(c);
    std::cout <<  "You Have Drawn: " << deck.DeckMap->at(c) << ", Cost: "<< c <<std::endl;
    std::cout << "Draw again? Y/N" << std::endl;
    std::cin >> response;

    while(response != "n")
    {
        c = deck.draw();
        hand.HandList->push_back(c);
        std::cout <<  "You Have Drawn: " << deck.DeckMap->at(c) << ", Cost: "<< c << std::endl;
        std::cout << "Draw again? Y/N" << std::endl;
        std::cin >> response;
    }

    std::cout << "Your hand is: " << std::endl;
    for(int i = 0; i < hand.HandList->size(); i++)
    {
        std::cout << deck.DeckMap->at(hand.HandList->at(i)) << ", Cost: "<< hand.HandList->at(i) << std::endl;
    }

    return 0;
};
