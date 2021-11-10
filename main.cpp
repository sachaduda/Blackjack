#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

enum class Suit 
{
  SPADES,
  CLUBS,
  DIAMONDS,
  HEARTS
};

enum class Rank : int
{
  ACE = 1,
  DEUCE,
  TROIKA,
  FOUR,
  CINQUE,
  SIX,
  SEVEN,
  EIGHT,
  NINE,
  TEN,
  JACK,
  QUEEN,
  KING
};

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

class Card
{
public:
  Card(Suit suit_, Rank rankCard_, bool isFaceUp_) : suit(suit_),
      rankCard(rankCard_), isFaceUp(isFaceUp_) {}

  void flip()
  {
    isFaceUp = !(isFaceUp);
  }

  int getValue() const
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

  friend std::ostream& operator << (std::ostream& out, const Card& card)
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

private:
  Suit suit;
  Rank rankCard;
  bool isFaceUp;
};

class Hand
{
public:
  Hand() 
  {
    arr_Cards.reserve(7);
  }

  virtual ~Hand()
  {
    clear();
  }

  void addCard(Card* card)
  {
    arr_Cards.push_back(card);
  }

  void clear()
  {
    std::vector<Card*>::iterator iter = arr_Cards.begin();
    for (iter = arr_Cards.begin(); iter != arr_Cards.end(); ++iter)
    {
      delete *iter;
      *iter = 0;
    }
    arr_Cards.clear();
  }

  int getTotal() const
  {
    int sumValue = 0;
    if (arr_Cards.empty())
    {
      return 0;
    }
    if ((int)arr_Cards[0]->getValue() == 0)
    {
      return 0;
    }

    for (int i = 0; i < arr_Cards.size(); i++)
    {
      sumValue += (int)arr_Cards.at(i)->getValue();
    }

    bool containsAce = false;
    for (int i = 0; i < arr_Cards.size(); i++)
    {
      if (arr_Cards.at(i)->getValue() == (int)Rank::ACE)
      {
        containsAce = true;
      }
    }
    if (containsAce && sumValue <= 11)
    {
      sumValue += 10;
    }

    return sumValue;
  }

protected:
  std::vector<Card*> arr_Cards;
};

class GenericPlayer : public Hand
{
public:
  GenericPlayer(const std::string name_) : name(name_) {}
  virtual ~GenericPlayer() {}

  virtual bool isHitting() const = 0;
  
  bool isBoosted() const
  {
    return (getTotal() > 21);
  }

  void bust() 
  {
    std::cout << name << " busts." << std::endl;
  }

  friend std::ostream& operator << (std::ostream& out, const GenericPlayer& player)
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
protected:
  std::string name;
};

class Player : public GenericPlayer
{
public:
  Player(const std::string& name_ = " ") : GenericPlayer(name_){}
  virtual ~Player(){}

  virtual bool isHitting() const override
  {
    char answer;
    std::cout << name << ", do you want a hit? (Y/N): ";
    std::cin >> answer;
    return (answer == 'y' || answer == 'Y');
  }

  void win() const
  {
    std::cout << name << " won!" << std::endl;
  }

  void lose() const
  {
    std::cout << name << " lost!" << std::endl;
  }

  void push() const 
  {
    std::cout << name << " played to a draw!" << std::endl;
  }
};

class House : public GenericPlayer
{
public:
  House(const std::string& name_ = "House") : GenericPlayer(name_) {} ;
  virtual ~House(){}

  virtual bool isHitting() const override
  {
    return (getTotal() <= 16);
  }

  void flipFirstCard() 
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
};

class Deck : public Hand
{
public:
  Deck() 
  { 
    arr_Cards.reserve(52);
    populate();
  }
  virtual ~Deck(){}

  void populate()
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

  void shuffle() 
  {
    std::random_shuffle(arr_Cards.begin(), arr_Cards.end());
  }

  void deal(Hand& hand) 
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

  void addltionalCards(GenericPlayer& player) 
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
};

class Game
{
public:
  Game (const std::vector<std::string> names_)
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
  ~Game(){}

  void play()
  {
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
    else
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
      }
    }
    for (itPlayers = players.begin(); itPlayers != players.end(); ++itPlayers)
    {
      itPlayers->clear();
    }
    house.clear();
  }

private:
  Deck deck;
  House house;
  std::vector<Player> players;
};



int main() 
{
  int numPlayers = 0;
  int count = 0;
  std::string buffer;
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
  Game game(vecNames);
  game.play();
}
