//
// Created by nariman on 20.02.20.
//

#pragma once

#include "game/controls.h"

class Player {
  float speed_y = 0;
  char step_x = '0';
  char symbol = '@';

  const Controls &controls;
  int x_;
  float y_;
  float max_jump_height_;
  float max_speed_y_;
  int ground_y_;
  float gravity_;

  bool IsFlying() const;

  void Render();

  void Move();

 public:
  Player(const Controls &controls, int x, float y, float max_jump_height, float max_speed_y, int ground_y,
         float gravity)
      : controls(controls),
        x_(x),
        y_(y),
        max_jump_height_(max_jump_height),
        max_speed_y_(max_speed_y),
        ground_y_(ground_y),
        gravity_(gravity) {}  // Горячие клавиши

  void Update();

  int GetX() const;
  int GetY() const;
};
