#include <BearLibTerminal.h>
#include <game/player.h>

int ToPos(float x);

void Player::Move() {
  if (controls_.IsJump() && !IsFlying()) {
    speed_y_ = max_speed_y_;
  }
  if (controls_.StepRight() && !IsFlying()) {
    x_ += 1;
  }
  if (controls_.StepLeft() && !IsFlying()) {
    x_ -= 1;
  }
  if (y_ >= ground_y_) {
    y_ = ground_y_;
  }
  if (y_ <= ground_y_ - max_jump_height_) {
    speed_y_ = 0;
  }

  y_ -= speed_y_;
  y_ += gravity_;
}

void Player::Render() {
  terminal_put(x_, ToPos(y_), symbol_);
}

bool Player::IsFlying() const {
  return y_ < ground_y_;
}

void Player::Update() {
  Move();
  Render();
}

int Player::GetX() const {
  return ToPos(x_);
}

int Player::GetY() const {
  return ToPos(y_);
}
