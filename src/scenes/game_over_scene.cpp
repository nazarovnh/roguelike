#include "game/scenes/game_over_scene.h"

#include <BearLibTerminal.h>
void GameOverScene::OnCreate() {}
void GameOverScene::OnRender() {
  terminal_print(1, 1, "Game Over\nScore is ?\nPress Enter to go to main menu");
  if (controls_.IsSubmit()) {
    ctx_->scene_ = "title";  // переходим на другую сцену
  }
}
void GameOverScene::OnExit() {}
GameOverScene::GameOverScene(Context *ctx, const Controls &controls) : IScene(ctx), controls_(controls) {}
