#include "Card.h"

Card::Card(Suit suit_, Rank rankCard_, bool isFaceUp_) : suit(suit_), rankCard(rankCard_), isFaceUp(isFaceUp_) {}

void Card::flip()
{
  isFaceUp = !(isFaceUp);
}

int Card::getValue() const
{
  int value = 0;
  if (isFaceUp)
  {
    value = (int)rankCard;
    if (value > 10)
    {
      value = 10;
    }
  }
  return value;
}

std::ostream& operator << (std::ostream& out, const Suit& suit)
{
  switch (suit)
  {
  case Suit::SPADES: return (out << "spades");
  case Suit::CLUBS: return (out << "clubs");
  case Suit::DIAMONDS: return (out << "diamonds");
  case Suit::HEARTS: return (out << "hearts");
  }
  return (out);
}

std::ostream& operator << (std::ostream& out, const Rank& rank)
{
  switch (rank)
  {
  case Rank::ACE: return (out << "A");
  case Rank::DEUCE: return (out << "2");
  case Rank::TROIKA: return (out << "3");
  case Rank::FOUR: return (out << "4");
  case Rank::CINQUE: return (out << "5");
  case Rank::SIX: return (out << "6");
  case Rank::SEVEN: return (out << "7");
  case Rank::EIGHT: return (out << "8");
  case Rank::NINE: return (out << "9");
  case Rank::TEN: return (out << "10");
  case Rank::JACK: return (out << "J");
  case Rank::QUEEN: return (out << "Q");
  case Rank::KING: return (out << "K");
  }
  return (out);
}

std::ostream& operator<<(std::ostream& out, const Card& card)
{
  if (!card.isFaceUp)
  {
    out << "XX";
  }
  else
  {
    out << card.rankCard << "<" << card.suit << ">";
  }
  return (out);
}
