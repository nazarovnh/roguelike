#pragma once
#include <vector>

#include "game/coins.h"
#include "game/player.h"

class CoinsManager {
  const Player *player_;
  int bag_coins_ = '0';
  float ground_y_ = 0;
  int world_width_;
  float speed_x_;
  std::vector<Coins> coins{{65, ground_y_}, {95, ground_y_}};

 public:
  CoinsManager(const Player *player, float ground_y, int world_width, float speed_x)
      : player_(player), ground_y_(ground_y), world_width_(world_width), speed_x_(speed_x) {}

  void Update();

  void GetCoins();
};
