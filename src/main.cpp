#include <BearLibTerminal.h>

#include <vector>

#include "game/coins.h"
#include "game/coinsmanager.h"
#include "game/controls.h"
#include "game/ground.h"
#include "game/math-utils.h"
#include "game/obstaclesmanager.h"
#include "game/player.h"

int main() {
  terminal_open();
  terminal_refresh();

  const int width = 80;
  const int ground_y = 15;
  const float gravity = 0.2;

  Controls controls{};
  Player player(controls, 2, ground_y - 3, 4.5, gravity * 3, ground_y, gravity);
  ObstaclesManager om(player, ground_y, width, 0.25);
  CoinsManager cm(player, ground_y, width, 0.25);
  Ground ground{'^', width, ground_y};

  // Ждем, пока пользователь не закроет окно
  while (true) {
    terminal_clear();

    controls.Update();

    om.Update();

    cm.Update();

    if (controls.IsExit()) {
      break;
    }

    player.Update();

    ground.Update();

    terminal_refresh();
  }
  terminal_close();
}
