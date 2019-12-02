#include "Card.h"

Card::Card(Cards c)
{
    card = new Cards(c);
}

Card::~Card()
{
    if (card)
        delete card;
}

Cards Card::GetRawCard()
{
    return *card;
}

Card CardFactory::CreateCard(Cards c)
{
    return Card(c);
}