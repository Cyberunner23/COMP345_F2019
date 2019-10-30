#include "Deck.h"
#include <iostream>



Deck::Deck()
{
    Hand = new std::vector<Cards>();
    CardList = new std::vector<Cards> {
            f1,f2,f3,f4,f5,f6,f7,f8,
            c1, c2, c3 ,c4, c5, c6, c7, c8, c9 ,c10,
            a1, a2, a3, a4, a5, a6, a7, a8, a9,
            o1, o2, o3, o4, o5, o6, o7,
            cr1, cr2, cr3, cr4, cr5
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

}

Deck::~Deck()
{
    delete Hand;
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
