//
// Created by nariman on 27.02.2020.
//
#include <BearLibTerminal.h>
#include <game/coinsmanager.h>
#include <game/math-utils.h>

void CoinsManager::Update() {
  // Почему указатель ?
  for (auto &a : coins) {
    a.x -= speed_x;
    if (a.x <= 0) {
      a.x = world_width;
    }

    a.Update();
  }
}
