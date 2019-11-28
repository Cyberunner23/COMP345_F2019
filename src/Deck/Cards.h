#pragma once
#include <string>

class Cards
{
public:
  Cards();
  Cards(string e, string t, int i);
  ~Cards();

  string* effect;
  string* type;
  int* id;

}
