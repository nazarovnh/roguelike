#pragma once
#include <vector>

#include "game/obstacle.h"
#include "game/player.h"
#include "iostream"

class ObstaclesManager {
  Player *player_;
  std::vector<Obstacle> obstacles_{{30, 20}, {30, 21}, {30, 22}};
  // bool is_hit_ = false;

 public:
  explicit ObstaclesManager(Player *player) : player_(player) {}

  void Update();
  void IsHit();
};
