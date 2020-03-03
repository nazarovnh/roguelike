//
// Created by nariman on 27.02.2020.
//
#include <BearLibTerminal.h>
#include <game/coinsmanager.h>
#include <game/math-utils.h>

void CoinsManager::GetCoins() {
  bag_coins += 1;
}

void CoinsManager::Update() {
  // Почему указатель ?
  int i = 0;
  terminal_put(73, 1, '$');
  terminal_put(75, 1, bag_coins);
  for (auto &a : coins) {
    a.x -= speed_x;
    if (a.x <= 0) {
      a.x = world_width;
    }

    if (player_.GetX() - 1 == to_pos(a.x) && player_.GetY() == to_pos(ground_y)) {
      GetCoins();
      coins.erase(coins.begin() + i);
    }

    a.Update();

    i += 1;
  }
}
