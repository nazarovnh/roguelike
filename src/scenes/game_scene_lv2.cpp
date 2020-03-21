#include "game/scenes/game_scene_lv2.h"
GameSceneLv2::GameSceneLv2(Context* ctx, const Controls& controls) : IScene(ctx), controls_(controls) {}
void GameSceneLv2::OnCreate() {
  player_ = new Player(controls_, 40, 10);
  om_ = new ObstaclesManager(player_);
  cm_ = new CoinsManager(player_);
  dr_ = new Door(player_, 79, 24);
  // Ругался на то что в конструкторе в .h передавал ссылку, а не указатель почему?
}
void GameSceneLv2::OnRender() {
  om_->Update();
  cm_->Update();
  //    if (om_->IsHit()) {
  //      ctx_->scene_ = "game_over";  // переходим на другую сцену
  //      return;
  //    }
  if (dr_->LevelUp()) {
    ctx_->scene_ = "game_over";  // переходим на другую сцену
    return;
  }
  player_->Update();
}

void GameSceneLv2::OnExit() {
  delete player_;
  delete om_;
}
