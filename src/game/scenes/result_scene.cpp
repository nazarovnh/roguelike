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
  // auto a = engine.GetEntityManager()->Get(8);
  //  auto sb = a->Get<ScoreBoardComponent>();
  terminal_print(1, 1, "Score is  \nPress Enter to go to next level");

  char str_1[20];
  // char str_2[20];

  snprintf(str_1, sizeof(str_1), "%d", ctx_->score_step);
  // snprintf(str_2, sizeof(str_2), "%d", scoreboard->score_coins_);
  terminal_print(10, 1, str_1);
  if (controls_.IsPressed(TK_ENTER)) {
    //      if (ctx_->scene_ == "game_lv1") {
    //        ctx_->scene_ = "game_lv2";
    //      } else if (ctx_->scene_ == "game_lv2") {
    //        ctx_->scene_ = "game_lv1";
    //      }
    ctx_->scene_ = "game_lv2";
  }
  terminal_refresh();
}
void ResultScene::OnExit() {
  ctx_->score_step = 0;
}

//  char str_step[20];
//  char str_coins[20];
//  snprintf(str_step, sizeof(str_step), "%d", controls_.step_x);
//  snprintf(str_coins, sizeof(str_coins), "%d", cm_.bag_coins_);
//
//  terminal_print(30, 5, "Your result:\n");
//  terminal_put(30, 7, '@');
//  terminal_print(32, 7, str_step);
//  terminal_put(30, 8, '$');
//  terminal_print(32, 8, str_coins);
//  terminal_print(30, 10, "Press Enter to continue");

//  controls_.step_x = 0;
//  //  cm_.bag_coins_ = 0;
//  if (controls_.IsPressed()) {
//    ctx_->scene_ = "game_scene_lv2";  // переходим на другую сцену
//  }
