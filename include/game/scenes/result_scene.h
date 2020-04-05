#pragma once

#include "game/coins-manager.h"
#include "game/controls.h"
#include "lib/scenes/i_scene.h"

class ResultScene : public IScene {
  const Controls& controls_;
  const CoinsManager& cm_;

 public:
  ResultScene(Context* ctx, const Controls& controls, const CoinsManager& cm);

  void OnCreate() override;
  void OnRender() override;
  void OnExit() override;
};
