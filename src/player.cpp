//  #include <BearLibTerminal.h>
//  #include <game/player.h>
//
//  int ToPos(float x);
//
//  void Player::Move() {
//    if (controls_.StepRight()) {
//      x_ += 1;
//    }
//    if (controls_.StepLeft()) {
//      x_ -= 1;
//    }
//    if (controls_.StepUp()) {
//      y_ -= 1;
//    }
//    if (controls_.StepDown()) {
//      y_ += 1;
//    }
//  }
//
//  void Player::Render() {
//    terminal_put(x_, y_, symbol_);
//  }
//
//  void Player::Update() {
//    Move();
//    Render();
//    char str[20];
//    snprintf(str, sizeof(str), "%d", controls_.step_x);
//    terminal_put(73, 0, '@');
//    terminal_print(75, 0, str);
//  }
//
//  int Player::GetX() const {
//    return x_;
//  }
  //
//  int Player::GetY() const {
//    return y_;
//  }
