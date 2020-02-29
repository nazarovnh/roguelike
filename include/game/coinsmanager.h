//
// Created by nariman on 27.02.2020.
//

#pragma once
#include <vector>

#include "game/coins.h"
#include "game/player.h"

class CoinsManager {
  const Player &player_;
  float ground_y = 0;
  int world_width;
  float speed_x;
  std::vector<Coins> coins{{59, ground_y}, {65, ground_y}};

 public:
  CoinsManager(const Player &player, float ground_y, int world_width, float speed_x)
      : player_(player), ground_y(ground_y), world_width(world_width), speed_x(speed_x) {}

  void Update();
};
