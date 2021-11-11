#include "House.h"

House::House(const std::string& name_) : GenericPlayer(name_) {}
House::~House() {}

bool House::isHitting() const
{
  return (getTotal() <= 16);
}

void House::flipFirstCard()
{
  if (!arr_Cards.empty())
  {
    arr_Cards.at(0)->flip();
  }
  else
  {
    std::cout << "No card to flip!" << std::endl;
  }
}
