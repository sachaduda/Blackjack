#include "Player.h"

Player::Player(const std::string& name_) : GenericPlayer(name_) {}
Player::~Player() {}

bool Player::isHitting() const
{
  char answer;
  std::cout << name << ", do you want a hit? (Y/N): ";
  std::cin >> answer;
  return (answer == 'y' || answer == 'Y');
}

void Player::win() const
{
  std::cout << std::endl << name << " won!" << std::endl;
}

void Player::lose() const
{
  std::cout << std::endl << name << " lost!" << std::endl;
}

void Player::push() const
{
  std::cout << std::endl << name << " played to a draw!" << std::endl;
}
