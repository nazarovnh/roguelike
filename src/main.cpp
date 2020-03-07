#include <BearLibTerminal.h>

#include "game/controls.h"
#include "game/scenes/game_over_scene.h"
#include "game/scenes/game_scene.h"
#include "game/scenes/title_scene.h"
#include "lib/scene_manager.h"

int main() {
  terminal_open();
  terminal_refresh();

  Controls controls;

  Context ctx{};  // создаем контекст на стеке в самом начале приложения
  SceneManager sm(ctx);  // создаем менеджер сцен на стеке

  // Регистрируем сцены в менеджер. Обратите внимание,
  // что деструкторы над сценами вызывать здесь не надо, так как изх вызовет менеджер.
  sm.Put("title", new TitleScene(&ctx, controls));
  sm.Put("game", new GameScene(&ctx, controls));
  sm.Put("game_over", new GameOverScene(&ctx, controls));

  // Выставляем текущую сцену
  ctx.scene_ = "title";

  // Ждем, пока пользователь не закроет окно
  while (true) {
    terminal_clear();

    controls.Update();
    if (controls.IsExit()) {
      break;
    }

    sm.OnRender();

    terminal_refresh();
  }
  sm.OnExit();

  terminal_close();
}
