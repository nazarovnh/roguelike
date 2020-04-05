//  #include <BearLibTerminal.h>
//  #include <game/coins-manager.h>
  //
//  int ToPos(float x);
  //
//  // CoinsManager::CoinsManager()  = default;
  //
//  void CoinsManager::GetCoins() {
//    bag_coins_ += 1;
//  }
  //
//  void CoinsManager::Update() {
//    // Почему указатель ?
//    int i = 0;
//    char str[20];
//    snprintf(str, sizeof(str), "%d", bag_coins_);
//    terminal_put(73, 1, '$');
//    terminal_print(75, 1, str);
//    for (auto& a : coins) {
//      if (player_->GetX() == ToPos(a.x_) && player_->GetY() == ToPos(a.y_)) {
//        GetCoins();
//        coins.erase(coins.begin() + i);
//      }
  //
//      a.Update();
  //
//      i += 1;
//    }
//  }
  //
//  CoinsManager::CoinsManager(const Player* player) : player_(player) {}
