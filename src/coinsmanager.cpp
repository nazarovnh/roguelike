#include <BearLibTerminal.h>
#include <game/coinsmanager.h>

int ToPos(float x);

void CoinsManager::GetCoins() {
  bag_coins_ += 1;
}

void CoinsManager::Update() {
  // Почему указатель ?
  int i = 0;
  terminal_put(73, 1, '$');
  terminal_put(75, 1, bag_coins_);
  for (auto &a : coins) {
    a.x_ -= speed_x_;
    if (a.x_ <= 0) {
      a.x_ = world_width_;
    }

    if (player_->GetX() - 1 == ToPos(a.x_) && player_->GetY() == ToPos(ground_y_)) {
      GetCoins();
      coins.erase(coins.begin() + i);
    }

    a.Update();

    i += 1;
  }
}
