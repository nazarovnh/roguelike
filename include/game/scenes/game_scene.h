#pragma once

#include "game/coinsmanager.h"
#include "game/ground.h"
#include "game/obstacle-manager.h"
#include "game/player.h"
#include "lib/i_scene.h"

class GameScene : public IScene {
  const int width_ = 80;
  const int ground_y_ = 15;
  const float gravity_ = 0.2;

  const Controls& controls_;
  Ground* ground_{};
  Player* player_{};
  ObstaclesManager* om_{};
  CoinsManager* cm_{};

 public:
  GameScene(Context* ctx, const Controls& controls);

  void OnCreate() override;
  void OnRender() override;
  void OnExit() override;
};
