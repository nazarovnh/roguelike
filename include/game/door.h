#pragma once

#include "game/player.h"

class Door {
  const Player *player_;
  char symbol_ = '>';
  bool level_up{};

 public:
  int x_;
  int y_;
  Door(Player *player, int x, int y) : player_(player), x_(x), y_(y) {}

  void Update();
  bool LevelUp();
};
