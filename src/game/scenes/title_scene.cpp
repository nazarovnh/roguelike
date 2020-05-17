#include "game/scenes/title_scene.h"
#include <BearLibTerminal.h>
void TitleScene::OnCreate() {}
void TitleScene::OnRender() {
    terminal_clear();
    terminal_print(1, 1, "Trex Game\nPress Enter to start");
    if (controls_.IsPressed(TK_ENTER)) {
        ctx_->scene_ = "game_lv1";  // переходим на другую сцену
        ctx_->prev_scene_ = "title";
    }
    terminal_refresh();
}
void TitleScene::OnExit() {}
TitleScene::TitleScene(Context *ctx, const Controls &controls) : IScene(ctx), controls_(controls) {}
