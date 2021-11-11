#include "Hand.h"

Hand::Hand()
{
  arr_Cards.reserve(7);
}

Hand::~Hand()
{
  clear();
}

void Hand::addCard(Card* card)
{
  arr_Cards.push_back(card);
}

void Hand::clear()
{
  std::vector<Card*>::iterator iter = arr_Cards.begin();
  for (iter = arr_Cards.begin(); iter != arr_Cards.end(); ++iter)
  {
    delete* iter;
    *iter = 0;
  }
  arr_Cards.clear();
}

int Hand::getTotal() const
{
  int sumValue = 0;
  if (arr_Cards.empty())
  {
    return 0;
  }
  if ((int)arr_Cards[0]->getValue() == 0)
  {
    return 0;
  }

  for (int i = 0; i < arr_Cards.size(); i++)
  {
    sumValue += (int)arr_Cards.at(i)->getValue();
  }

  bool containsAce = false;
  for (int i = 0; i < arr_Cards.size(); i++)
  {
    if (arr_Cards.at(i)->getValue() == (int)Rank::ACE)
    {
      containsAce = true;
    }
  }
  if (containsAce && sumValue <= 11)
  {
    sumValue += 10;
  }

  return sumValue;
}
