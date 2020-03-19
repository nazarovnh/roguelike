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
    if (player_->GetX() == ToPos(a.x_) && player_->GetY() == ToPos(a.y_)) {
      GetCoins();
      coins.erase(coins.begin() + i);
    }

    a.Update();

    i += 1;
  }
}
