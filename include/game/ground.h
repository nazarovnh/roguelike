#pragma once

class Ground {
  char symbol_;
  int width_;
  int y_;

 public:
  Ground(char symbol, int width, int y) : symbol_(symbol), width_(width), y_(y) {}

  void Update();
};
