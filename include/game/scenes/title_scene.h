#pragma once

#include "game/controls.h"
#include "lib/i_scene.h"

class TitleScene : public IScene {
  const Controls& controls_;

 public:
  TitleScene(Context* ctx, const Controls& controls);
  void OnCreate() override;
  void OnRender() override;
  void OnExit() override;
};
