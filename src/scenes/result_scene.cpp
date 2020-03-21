#include "game/scenes/result_scene.h"

#include <BearLibTerminal.h>

ResultScene::ResultScene(Context* ctx, const Controls& controls, const CoinsManager& cm)
    : IScene(ctx), controls_(controls), cm_(cm) {}

void ResultScene::OnCreate() {}

void ResultScene::OnRender() {
  char str_step[20];
  char str_coins[20];
  snprintf(str_step, sizeof(str_step), "%d", controls_.step_x);
  snprintf(str_coins, sizeof(str_coins), "%d", cm_.bag_coins_);

  terminal_print(30, 5, "Your result:\n");
  terminal_put(30, 7, '@');
  terminal_print(32, 7, str_step);
  terminal_put(30, 8, '$');
  terminal_print(32, 8, str_coins);
  terminal_print(30, 10, "Press Enter to continue");

  //  controls_.step_x = 0;
  //  cm_.bag_coins_ = 0;
  if (controls_.IsSubmit()) {
    ctx_->scene_ = "game_scene_lv2";  // переходим на другую сцену
  }
}
void ResultScene::OnExit() {}
