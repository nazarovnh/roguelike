#include "game/scenes/title_scene.h"

#include <BearLibTerminal.h>
void TitleScene::OnCreate() {}
void TitleScene::OnRender() {
  terminal_print(1, 1, "Game\nPress Enter to start");
  if (controls_.IsSubmit()) {
    ctx_->scene_ = "game_scene_lv1";  // переходим на другую сцену
  }
}
void TitleScene::OnExit() {}
TitleScene::TitleScene(Context *ctx, const Controls &controls) : IScene(ctx), controls_(controls) {}
