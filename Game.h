#pragma once

#include "Deck.h"
#include "Player.h"
#include "House.h"

#include <vector>
#include <string>

class Game
{
public:
  Game(const std::vector<std::string> names_);
  ~Game();

  void play();
  
private:
  Deck deck;
  House house;
  std::vector<Player> players;
};
