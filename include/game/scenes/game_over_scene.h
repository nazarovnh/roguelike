#pragma once

#include "game/controls.h"
#include "lib/scenes/i_scene.h"

class GameOverScene : public IScene {
  const Controls& controls_;

 public:
  GameOverScene(Context* ctx, const Controls& controls);
  void OnCreate() override;
  void OnRender() override;
  void OnExit() override;
};
