//
// Created by nariman on 21.02.20.
//

#include <BearLibTerminal.h>
#include <game/obstaclesmanager.h>

#include "game/math-utils.h"

void ObstaclesManager::Gameover() {
  while (!terminal_has_input()) {
    terminal_print(1, 1, "Game Over! Print anything");
    terminal_refresh();
  }
}

void ObstaclesManager::Update() {
  // Почему указатель ?
  for (auto &o : obstacles) {
    o.x -= speed_x;
    if (o.x <= 0) {
      o.x = world_width;
    }

    if (player_.GetX() - 1 == to_pos(o.x) && player_.GetY() == to_pos(ground_y)) {
      Gameover();
    }

    o.Update();
  }
}
