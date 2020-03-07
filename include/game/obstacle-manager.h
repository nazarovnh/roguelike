#pragma once

#include <vector>

#include "game/obstacle.h"
#include "game/player.h"

class ObstaclesManager {
  const Player *player_;
  float ground_y_ = 0;
  int world_width_;
  float speed_x_;
  std::vector<Obstacle> obstacles_{{30, ground_y_}, {55, ground_y_}, {70, ground_y_}};
  bool is_hit_ = false;

 public:
  ObstaclesManager(const Player *player, float ground_y, int world_width, float speed_x)
      : player_(player), ground_y_(ground_y), world_width_(world_width), speed_x_(speed_x) {}

  void Update();
  bool IsHit() const;
};

