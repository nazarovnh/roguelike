#include "game/scenes/result_scene.h"

#include <BearLibTerminal.h>

#include "game/components/scoreboard_component.h"
#include "lib/ecs/entity_manager.h"

ResultScene::ResultScene(Context* ctx, const Controls& controls) : IScene(ctx), controls_(controls) {}

void ResultScene::OnCreate() {}

static bool Filter2(const Entity& entity) {
  return entity.Contains<ColliderComponent>() && entity.Contains<ScoreBoardComponent>();
}

void ResultScene::OnRender() {
  terminal_clear();
  terminal_print(
      1, 1, "Congratulations you have passed the level. Your Score is:   \n\n\n\n\n\nPress Enter to go to next level");
  terminal_print(1, 3, "steps:");
  terminal_print(1, 5, "coins:");
  char str_1[20];
  char str_2[20];

  snprintf(str_1, sizeof(str_1), "%d", ctx_->score_steps);
  snprintf(str_2, sizeof(str_2), "%d", ctx_->score_coins);
  terminal_print(8, 3, str_1);
  terminal_print(8, 5, str_2);
  if (controls_.IsPressed(TK_ENTER)) {
    if (ctx_->prev_scene_ == "game_lv1") {
      ctx_->scene_ = "game_lv2";
    } else if (ctx_->prev_scene_ == "game_lv2") {
      ctx_->scene_ = "game_lv3";
    } else if (ctx_->prev_scene_ == "game_lv3") {
      ctx_->scene_ = "title";
    }
  }
  terminal_refresh();
}
void ResultScene::OnExit() {
  //  ctx_->score_steps = 0;
  //  ctx_->score_coins = 0;
}
