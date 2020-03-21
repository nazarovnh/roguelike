#include "game/scenes/game_scene_lv1.h"
GameSceneLv1::GameSceneLv1(Context* ctx, const Controls& controls) : IScene(ctx), controls_(controls) {}
void GameSceneLv1::OnCreate() {
  player_ = new Player(controls_, 2, 2);
  om_ = new ObstaclesManager(player_);
  cm_ = new CoinsManager(player_);
  dr_ = new Door(player_, 79, 24);
  // Ругался на то что в конструкторе в .h передавал ссылку, а не указатель почему?
}
void GameSceneLv1::OnRender() {
  player_->Update();
  om_->Update();
  cm_->Update();
  dr_->Update();
  //    if (om_->IsHit()) {
  //      ctx_->scene_ = "game_over";  // переходим на другую сцену
  //      return;
  //    }

  if (dr_->LevelUp()) {
    ctx_->scene_ = "result";  // переходим на другую сцену
    return;
  }
}
void GameSceneLv1::OnExit() {
  delete player_;
  delete cm_;
  delete dr_;
  delete om_;
}
