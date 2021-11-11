#include "Deck.h"
#include <algorithm>

Deck::Deck()
{
  arr_Cards.reserve(52);
  populate();
}

Deck::~Deck() {}

void Deck::populate()
{
  clear();
  for (Suit i = Suit::SPADES; i <= Suit::HEARTS; i = static_cast<Suit>((int)i + 1))
  {
    for (Rank j = Rank::ACE; j <= Rank::KING; j = static_cast<Rank>((int)j + 1))
    {
      addCard(new Card(static_cast<Suit>(i), static_cast<Rank>(j), true));
    }
  }
}

void Deck::shuffle()
{
  std::random_shuffle(arr_Cards.begin(), arr_Cards.end());
}

void Deck::deal(Hand& hand)
{
  if (!arr_Cards.empty())
  {
    hand.addCard(arr_Cards.back());
    arr_Cards.pop_back();
  }
  else
  {
    std::cout << "Out of cards. Unable to deal.";
  }
}

void Deck::addltionalCards(GenericPlayer& player)
{
  std::cout << std::endl;
  while (!(player.isBoosted()) && player.isHitting())
  {
    deal(player);
    std::cout << player;
    if (player.isBoosted())
    {
      player.bust();
    }
  }
}
