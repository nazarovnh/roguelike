//
// Created by nariman on 27.02.2020.
//

#pragma once

class Coins {
 private:
  char sybmol = '$';

 public:
  float x;
  float y;

  Coins(float x, float y) : x(x), y(y) {}

  void Update();
};
