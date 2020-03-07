#pragma once

class Obstacle {
  char symbol_ = '#';

 public:
  float x_;
  float y_;

  Obstacle(float x, float y) : x_(x), y_(y) {}

  void Update();
};
