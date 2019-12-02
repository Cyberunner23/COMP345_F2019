#include "Card.h"

Card::Card(Cards c)
{
    card = new Cards(c);
}

Cards Card::GetRawCard()
{
    return *card;
}

Card CardFactory::CreateCard(Cards c)
{
    return Card(c);
}