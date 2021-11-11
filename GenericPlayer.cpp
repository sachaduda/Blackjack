#include "GenericPlayer.h"

GenericPlayer::GenericPlayer(const std::string name_) : name(name_) {}

GenericPlayer::~GenericPlayer() {}

bool GenericPlayer::isBoosted() const
{
  return (getTotal() > 21);
}

void GenericPlayer::bust()
{
  std::cout << std::endl  << name << " busts." << std::endl;
}

std::ostream& operator<<(std::ostream& out, const GenericPlayer& player)
{
  out << player.name << ":\t";

  std::vector<Card*>::const_iterator pCard;
  if (!player.arr_Cards.empty())
  {
    for (pCard = player.arr_Cards.begin(); pCard != player.arr_Cards.end(); ++pCard)
    {
      out << *(*pCard) << "\t";
    }

    if (player.getTotal() != 0)
    {
      std::cout << "(" << player.getTotal() << ")" << std::endl;
    }
  }
  else
  {
    out << "<empty>";
  }

  return (out);
}
