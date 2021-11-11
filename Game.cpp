#include "Game.h"

Game::Game(const std::vector<std::string> names_)
{
  std::vector<std::string>::const_iterator itName;
  for (itName = names_.begin(); itName != names_.end(); ++itName)
  {
    players.push_back(Player(*itName));
  }
  srand(static_cast<unsigned int>(time(0)));
  deck.populate();
  deck.shuffle();
}

Game::~Game() {}

void Game::play()
{
  char answer;
  std::vector<Player>::iterator itPlayers;
  for (int i = 0; i < 2; i++)
  {
    for (itPlayers = players.begin(); itPlayers != players.end(); ++itPlayers)
    {
      deck.deal(*itPlayers);
    }
    deck.deal(house);
  }
  house.flipFirstCard();
  for (itPlayers = players.begin(); itPlayers != players.end(); ++itPlayers)
  {
    std::cout << *itPlayers << std::endl;
  }
  std::cout << house << std::endl;
  for (itPlayers = players.begin(); itPlayers != players.end(); ++itPlayers)
  {
    deck.addltionalCards(*itPlayers);
  }
  house.flipFirstCard();
  std::cout << std::endl << house;
  deck.addltionalCards(house);
  if (house.isBoosted())
  {
    for (itPlayers = players.begin(); itPlayers != players.end(); ++itPlayers)
    {
      if (!(itPlayers->isBoosted()))
      {
        itPlayers->win();
      }
    }
  }
  else if (!(house.isBoosted()))
  {
    for (itPlayers = players.begin(); itPlayers != players.end(); ++itPlayers)
    {
      if (!(itPlayers->isBoosted()))
      {
        if (itPlayers->getTotal() > house.getTotal())
        {
          itPlayers->win();
        }
        else if (itPlayers->getTotal() < house.getTotal())
        {
          itPlayers->lose();
        }
        else if (itPlayers->getTotal() == house.getTotal())
        {
          itPlayers->push();
        }
      }
      else
      {
        itPlayers->lose();
      }
    }
  }
  else if ((house.isBoosted()) && (itPlayers->isBoosted()))
  {
    std::cout << "Nobody won!" << std::endl;
  }

  for (itPlayers = players.begin(); itPlayers != players.end(); ++itPlayers)
  {
    itPlayers->clear();
  }
  house.clear();
  std::cout << std::endl << "Want to play some more ? (Y/N)" << std::endl;
  std::cin >> answer;
  if (answer == 'y' || answer == 'Y')
  {
    system("cls");
    play();
  }
  else
  {
    std::cout << "Bay!" << std::endl;
  }
}
