#pragma once

#include "Hand.h"

class GenericPlayer : public Hand
{
public:
  GenericPlayer(const std::string name_);
  virtual ~GenericPlayer();

  virtual bool isHitting() const = 0;
  bool isBoosted() const;
  void bust();

  friend std::ostream& operator << (std::ostream& out, const GenericPlayer& player);

protected:
  std::string name;
};
