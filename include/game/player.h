#pragma once

#include "game/controls.h"
class Player {
  char symbol_ = '@';

  const Controls &controls_;

  void Render();

  void Move();

 public:
  int x_;
  int y_;
  Player(const Controls &controls, int x, int y) : controls_(controls), x_(x), y_(y) {}

  void Update();

  int GetX() const;
  int GetY() const;
};
