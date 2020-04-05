#pragma once

#include "game/coins-manager.h"
#include "game/door.h"
#include "game/obstacle-manager.h"
#include "game/player.h"
#include "lib/scenes/i_scene.h"

class GameSceneLv2 : public IScene {
  const Controls& controls_;
  Player* player_{};
  ObstaclesManager* om_{};
  CoinsManager* cm_{};
  Door* dr_{};

 public:
  GameSceneLv2(Context* ctx, const Controls& controls);

  void OnCreate() override;
  void OnRender() override;
  void OnExit() override;
};
