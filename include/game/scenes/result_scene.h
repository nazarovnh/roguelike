#pragma once

#include "game/coins-manager.h"
#include "game/controls.h"
#include "lib/scenes/i_scene.h"

class ResultScene : public IScene {
  const Controls& controls_;

 public:
  ResultScene(Context* ctx, const Controls& controls);

  void OnCreate() override;
  void OnRender() override;
  void OnExit() override;
};
