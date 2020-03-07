#include <game/obstacle-manager.h>

#include "game/math-utils.h"

void ObstaclesManager::Update() {
  for (auto &o : obstacles_) {
    o.x_ -= speed_x_;
    if (o.x_ <= 0) {
      o.x_ = world_width_;
    }

    if (player_->GetX() == ToPos(o.x_) && player_->GetY() == ToPos(ground_y_)) {
      is_hit_ = true;
    }

    o.Update();
  }
}
bool ObstaclesManager::IsHit() const {
  return is_hit_;
}
