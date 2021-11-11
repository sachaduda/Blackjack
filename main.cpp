#include "Game.h"

#include <iostream>


int main() 
{
  int numPlayers = 0;
  std::string name;
  std::vector<std::string> vecNames;
  std::cout << "Enter the number of players: " << std::endl;
  std::cin >> numPlayers;
  std::cout << "Enter the names of the players: " << std::endl;
  for (int i = 0; i < numPlayers; i++)
  {
    std::cin >> name;
    vecNames.push_back(name);
  }
  system("cls");
  Game game(vecNames);
  game.play();
}
