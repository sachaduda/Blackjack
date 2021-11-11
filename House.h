#pragma once

#include "GenericPlayer.h"

class House : public GenericPlayer
{
public:
  House(const std::string& name_ = "House");
  virtual ~House();

  virtual bool isHitting() const override;
  void flipFirstCard();
};
