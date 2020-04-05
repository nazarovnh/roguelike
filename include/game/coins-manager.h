#pragma once
#include <vector>

#include "game/coins.h"
#include "game/player.h"

class CoinsManager {
  const Player* player_{};
  std::vector<Coins> coins{{65, 10}, {65, 11}};

 public:
  int bag_coins_ = 0;
  explicit CoinsManager(const Player* player);

  void Update();

  void GetCoins();
};
