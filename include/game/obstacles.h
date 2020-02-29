//
// Created by nariman on 20.02.20.
//

#pragma once

class Obstacles {
  char sybmol = '#';

 public:
  float x;
  float y;

  Obstacles(float x, float y) : x(x), y(y) {}

  void Update();
};
