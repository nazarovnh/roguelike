#pragma once
#include <vector>

#include "game/coins.h"
#include "game/player.h"

class CoinsManager {
  const Player *player_;
  int bag_coins_ = '0';
  std::vector<Coins> coins{{65, 10}, {65, 11}};

 public:
  explicit CoinsManager(const Player *player) : player_(player) {}

  void Update();

  void GetCoins();
};
