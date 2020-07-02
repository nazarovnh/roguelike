#include "game/scenes/game_over_scene.h"

#include <BearLibTerminal.h>
void GameOverScene::OnCreate() {}
void GameOverScene::OnRender() {
  terminal_clear();
  terminal_print(1, 1, "Game Over. Your Score is:   \n\n\n\n\n\nPress Enter to go to main menu");
  terminal_print(1, 3, "steps:");
  terminal_print(1, 5, "coins:");
  char str_1[20];
  char str_2[20];

  snprintf(str_1, sizeof(str_1), "%d", ctx_->score_steps);
  snprintf(str_2, sizeof(str_2), "%d", ctx_->score_coins);
  terminal_print(8, 3, str_1);
  terminal_print(8, 5, str_2);

  if (controls_.IsPressed(TK_ENTER)) {
    ctx_->levels_.clear();
    ctx_->level_number = 0;
    ctx_->scene_ = "title";
  }
  terminal_refresh();
}
void GameOverScene::OnExit() {}
GameOverScene::GameOverScene(Context *ctx, const Controls &controls) : IScene(ctx), controls_(controls) {}
