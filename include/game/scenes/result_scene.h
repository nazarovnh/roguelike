#pragma once

#include "game/coinsmanager.h"
#include "game/controls.h"
#include "lib/i_scene.h"

class ResultScene : public IScene {
  const Controls& controls_;
  const CoinsManager& cm_;

 public:
  ResultScene(Context* ctx, const Controls& controls, const CoinsManager& cm);

  void OnCreate() override;
  void OnRender() override;
  void OnExit() override;
};
