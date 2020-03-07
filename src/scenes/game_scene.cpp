#include "game/scenes/game_scene.h"
GameScene::GameScene(Context* ctx, const Controls& controls) : IScene(ctx), controls_(controls) {}
void GameScene::OnCreate() {
  ground_ = new Ground('^', width_, ground_y_);
  player_ = new Player(controls_, 2, ground_y_ - 3.0f, 4.5, gravity_ * 3, ground_y_, gravity_);
  om_ = new ObstaclesManager(player_, ground_y_, width_, 0.25);
  cm_ = new CoinsManager(player_, ground_y_, width_, 0.25);
  // Ругался на то что в конструкторе в .h передавал ссылку, а не указатель почему?
}
void GameScene::OnRender() {
  om_->Update();
  cm_->Update();
  if (om_->IsHit()) {
    ctx_->scene_ = "game_over";  // переходим на другую сцену
    return;
  }
  player_->Update();
  ground_->Update();
}
void GameScene::OnExit() {
  delete ground_;
  delete player_;
  delete om_;
}
