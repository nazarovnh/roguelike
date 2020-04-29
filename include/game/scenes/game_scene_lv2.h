#pragma once

#include <lib/ecs/engine.h>

#include "game/coins-manager.h"
#include "game/door.h"
#include "game/obstacle-manager.h"
#include "game/player.h"
#include "lib/scenes/i_scene.h"

class GameSceneLv2 : public IScene {
  const int width_ = 80;
  const int ground_y_ = 15;
  const Engine engine{};
  const Controls& controls;

 public:
  GameSceneLv2(Context* const ctx, const Controls& controls);

  void OnCreate() override;
  void OnRender() override;
  void Check();
  void OnExit() override;
};
