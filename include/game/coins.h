#pragma once

class Coins {
 private:
  char sybmol_ = '$';

 public:
  float x_;
  float y_;

  Coins(float x, float y) : x_(x), y_(y) {}

  void Update();
};
