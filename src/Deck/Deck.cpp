#include "Deck.h"
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <random>
#include <chrono>



Deck::Deck()
{

  CardList = new std::vector<Cards>
  {
    Cards("Move 3 Armies", "Forest", 1);
    Cards("Add 3 Armies", "Forest", 2);
    Cards("Destroy 1 Army or Build City", "Forest", 3);
    Cards("Add 2 Armies or Move 3 Armies", "Forest", 4);
    Cards("Move 4 Armies via Ship", 5);
    Cards("Build City", "Forest", 6);
    Cards("Move 3 Armies via Ship", "Forest", 7);
    Cards("Move 6 Armies*", "Forest", 8);

    Cards("Build City", "Carrots", 9);
    Cards("Destroy 1 Army and Add 1 Army", "Carrots", 10);
    Cards("Add 3 Armies", "Carrots", 11);
    Cards("Move 4 Armies", "Carrots", 12);
    Cards("Move 5 Armies", "Carrots", 13);
    Cards("Add 3 Armies", "Carrots", 14);
    Cards("Move 3 Armies via Ship", "Carrots", 15);
    Cards("Move 4 Armies", "Carrots", 16);
    Cards("Build City", "Carrots", 17);
    Cards("Add 4 Armies or Move 2 Armies*", "Carrots", 18);

    Cards("Move 4 Armies", "Anvils", 19);
    Cards("Add 3 Armies or Move 4 Armies", "Anvils", 20);
    Cards("Move 5 Armies", "Anvils", 21);
    Cards("Add 3 Armies", "Anvils", 22);
    Cards("Add 3 Armies", "Anvils", 23);
    Cards("Move 3 Armies via Ship", "Anvils", 24);
    Cards("Build City", "Anvils", 25);
    Cards("Add 4 Armies or Move 3 Armies", "Anvils", 26);
    Cards("Move 4 Armies", "Anvils", 27);

    Cards("Move 2 Armies", "Ore", 28);
    Cards("Move 3 Armies via Ship", "Ore", 29);
    Cards("Move 2 Armies via Ship", "Ore", 30);
    Cards("Add 3 Armies", "Ore", 31);
    Cards("Add 3 Armies", "Ore", 32);
    Cards("Add 2 Armies", "Ore", 33);
    Cards("Move 2 Armies via Ship*", "Ore", 34);

    Cards("Add 2 Armies", "Crystals", 35);
    Cards("Add 2 Armies", "Crystals", 36);
    Cards("Move 2 Armies", "Crystals", 37);
    Cards("Add 1 Army", "Crystals", 38);
    Cards("Add 2 Armies", "Crystals", 39);
  };
  /*  CardList = new std::vector<Cards> {
            f1,f2,f3,f4,f5,f6,f7,f8,
            c1, c2, c3 ,c4, c5, c6, c7, c8, c9 ,c10,
            a1, a2, a3, a4, a5, a6, a7, a8, a9,
            o1, o2, o3, o4, o5, o6, o7,
            cr1, cr2, cr3, cr4, cr5
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
    };*/

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

Cards Deck::draw()
{
    Cards c;
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
  HandList = new std::vector<Cards>();
}

Hand::~Hand()
{
    delete HandList;
}

void Hand::exchange()
{

}
