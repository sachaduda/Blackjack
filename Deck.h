#pragma once

#include "GenericPlayer.h"

class Deck : public Hand
{
public:
  Deck();
  virtual ~Deck();

  void populate();
  void shuffle();
  void deal(Hand& hand);
  void addltionalCards(GenericPlayer& player);
};
