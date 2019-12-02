#include "Deck.h"
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <random>
#include <chrono>



Deck::Deck()
{
    CardList = new std::vector<Card>
    {
            CardFactory::CreateCard(f1),
            CardFactory::CreateCard(f2),
            CardFactory::CreateCard(f3),
            CardFactory::CreateCard(f4),
            CardFactory::CreateCard(f5),
            CardFactory::CreateCard(f6),
            CardFactory::CreateCard(f7),
            CardFactory::CreateCard(f8),
            CardFactory::CreateCard(c1),
            CardFactory::CreateCard(c2),
            CardFactory::CreateCard(c3 ),
            CardFactory::CreateCard(c4),
            CardFactory::CreateCard(c5),
            CardFactory::CreateCard(c6),
            CardFactory::CreateCard(c7),
            CardFactory::CreateCard(c8),
            CardFactory::CreateCard(c9 ),
            CardFactory::CreateCard(c10),
            CardFactory::CreateCard(a1),
            CardFactory::CreateCard(a2),
            CardFactory::CreateCard(a3),
            CardFactory::CreateCard(a4),
            CardFactory::CreateCard(a5),
            CardFactory::CreateCard(a6),
            CardFactory::CreateCard(a7),
            CardFactory::CreateCard(a8),
            CardFactory::CreateCard(a9),
            CardFactory::CreateCard(o1),
            CardFactory::CreateCard(o2),
            CardFactory::CreateCard(o3),
            CardFactory::CreateCard(o4),
            CardFactory::CreateCard(o5),
            CardFactory::CreateCard(o6),
            CardFactory::CreateCard(o7),
            CardFactory::CreateCard(cr1),
            CardFactory::CreateCard(cr2),
            CardFactory::CreateCard(cr3),
            CardFactory::CreateCard(cr4),
            CardFactory::CreateCard(cr5)
    };

    GoodsMap = new std::map<Cards, std::string>
    {
            //These are the forest cards
            {f1, "Forest"},
            {f2, "Forest"},
            {f3, "Forest"},
            {f4, "Forest"},
            {f5, "Forest"},
            {f6, "Forest"},
            {f7, "Forest"},
            {f8, "Forest"},
            //Carrot cards
            {c1, "Carrots"},
            {c2, "Carrots"},
            {c3, "Carrots"},
            {c4, "Carrots"},
            {c5, "Carrots"},
            {c6, "Carrots"},
            {c7, "Carrots"},
            {c8, "Carrots"},
            {c9, "Carrots"},
            {c10,"Carrots"},
            //Anvil Cards
            {a1, "Anvils"},
            {a2, "Anvils"},
            {a3, "Anvils"},
            {a4, "Anvils"},
            {a5, "Anvils"},
            {a6, "Anvils"},
            {a7, "Anvils"},
            {a8, "Anvils"},
            {a9, "Anvils"},
            //List of Ore cards
            {o1, "Ore"},
            {o2, "Ore"},
            {o3, "Ore"},
            {o4, "Ore"},
            {o5, "Ore"},
            {o6, "Ore"},
            {o7, "Ore"},
            //List of Crystal card
            {cr1, "Crystals"},
            {cr2, "Crystals"},
            {cr3, "Crystals"},
            {cr4, "Crystals"},
            {cr5, "Crystals"},

          };
    DeckMap = new std::map<Cards, std::string> {
            {f1, "Move 3 Armies"},
            {f2, "Add 3 Armies"},
            {f3, "Destroy 1 Army or Build City"},
            {f4, "Add 2 Armies or Move 3 Armies"},
            {f5, "Move 4 Armies via Ship"},
            {f6, "Build City"},
            {f7, "Move 3 Armies via Ship"},
            {f8, "Move 6 Armies*"},


            //10 CarrotCards{"Build City","Destroy 1 Army and Add 1 Army", "Add 3 Armies", "Move 4 Armies", "Move 5 Armies",
            //"Add 3 Armies (Double Carrot)", "Move 3 Armies via Ship", "Add 4 Armies or Move 2 Armies*", "Move 4 Armies", "Build City"};

            {c1, "Build City"},
            {c2, "Destroy 1 Army and Add 1 Army"},
            {c3, "Add 3 Armies"},
            {c4, "Move 4 Armies"},
            {c5, "Move 5 Armies"},
            {c6, "Add 3 Armies (DOUBLE)"},
            {c7, "Move 3 Armies via Ship"},
            {c8, "Move 4 Armies"},
            {c9, "Build City"},
            {c10,"Add 4 Armies or Move 2 Armies*"},

            // 9 AnvilCards "Move 4 Armies", "Add 3 Armies or Move 4 Armies", "Move 5 Armies", "Add 3 Armies", "Add 3 Armies",
            //"Move 3 Armies via Ship", "Build City", "Move 4 Armies (Double Anvil)*", "Add 4 Armies or Move 3 Armies"

            {a1, "Move 4 Armies"},
            {a2, "Add 3 Armies or Move 4 Armies"},
            {a3, "Move 5 Armies"},
            {a4, "Add 3 Armies"},
            {a5, "Add 3 Armies"},
            {a6, "Move 3 Armies via Ship"},
            {a7, "Build City"},
            {a8, "Add 4 Armies or Move 3 Armies"},
            {a9, "Move 4 Armies (DOUBLE)"},


            // 7 Ore Cards: "Move 2 Armies", "Move 3 Armies via Ship", "Move 2 Armies via Ship*", "Move 2 Armies via Ship",
            //"Add 3 Armies", "Add 3 Armies", "Add 2 Armies"

            {o1, "Move 2 Armies"},
            {o2, "Move 3 Armies via Ship"},
            {o3, "Move 2 Armies Via ship"},
            {o4, "Add 3 Armies"},
            {o5, "Add 3 Armies"},
            {o6, "Add 2 Armies"},
            {o7, "Move 2 Armies via Ship*"},


            // 5 Crystal Cards: "Add 2 Armies", "Add 2 Armies", "Move 2 Armies", "Add 1 Army", "Add 2 Armies*"

            {cr1, "Add 2 Armies"},
            {cr2, "Add 2 Armies"},
            {cr3, "Move 2 Armies"},
            {cr4, "Add 1 Army"},
            {cr5, "Add 2 Armies"},
    };

    CitiesMap = new std::map<Cities, std::string>
    {
        {Cities::RED, "RED"},
        {Cities::WHITE, "WHITE"},
        {Cities::BLUE, "BLUE"},
        {Cities::YELLOW, "YELLOW"},
        {Cities::GREEN, "GREEN"}
    };

    ArmiesMap = new std::map<Armies, std::string>
    {
        {Armies::RED, "RED"},
        {Armies::WHITE, "WHITE"},
        {Armies::BLUE, "BLUE"},
        {Armies::YELLOW, "YELLOW"},
        {Armies::GREEN, "GREEN"}
    };
}

Deck::~Deck()
{
    delete CardList;
    delete DeckMap;
}

Card Deck::draw()
{
    Card c;
    if(!CardList->empty())
    {
        c = CardList->back();
        CardList->pop_back();
    }

    return c;
}

void Deck::shuffleDeck()
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(CardList->begin(), CardList->end(), std::default_random_engine(seed));
}


Hand::Hand()
{
  HandList = new std::vector<Card>();
}

Hand::~Hand()
{
    delete HandList;
}

void Hand::exchange()
{

}
