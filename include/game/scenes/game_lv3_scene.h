#pragma once

#include <game/controls.h>
#include <lib/ecs/engine.h>

#include "lib/scenes/i_scene.h"

class GameSceneLv3 : public IScene {
  const Engine engine{};
  const Controls& controls;

 public:
  GameSceneLv3(Context* const ctx, const Controls& controls);

  void OnCreate() override;
  void OnRender() override;
  void OnExit() override;
};
