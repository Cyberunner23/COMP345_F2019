#include "Cards.h"

Cards::Cards()
{
  effect = "null";
  id = -1;
  type = "null";
}
Cards::Cards(string e, string t, int i)
{
  effect = e;
  type = t;
  id = i;
}
