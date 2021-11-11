#pragma once

#include "GenericPlayer.h"

class Player : public GenericPlayer
{
public:
  Player(const std::string& name_ = " ");
  virtual ~Player();

  virtual bool isHitting() const override;
  void win() const;
  void lose() const;
  void push() const;
};
