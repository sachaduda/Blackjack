#pragma once
#include "Card.h"

#include <vector>

class Hand
{
public:
  Hand();
  virtual ~Hand();
 
  void addCard(Card* card);
  void clear();
  int getTotal() const;

protected:
  std::vector<Card*> arr_Cards;
};
