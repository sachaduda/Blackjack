#pragma once

#include "EnumSuit.h"
#include "EnumRank.h"

#include <iostream>

class Card
{
public:
  Card(Suit suit_, Rank rankCard_, bool isFaceUp_);
  void flip();
  int getValue() const;
  friend std::ostream& operator << (std::ostream& out, const Card& card);

private:
  Suit suit;
  Rank rankCard;
  bool isFaceUp;
};
